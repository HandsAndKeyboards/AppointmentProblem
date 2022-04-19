#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "common/constants.h"
#include "common/json.h"

/** ******************************************** PRIVATE ********************************************* **/

QTime MainWindow::calculateTimeDelta(const QTime & start, const QTime & finish)
{
	return QTime::fromMSecsSinceStartOfDay(start.msecsTo(finish));
}

/// добавление 3Д окна на форму
void MainWindow::add3DWindow(Qt3DExtras::Qt3DWindow * window, int row, int column, int rowSpan, int columnSpan)
{
	container = QWidget::createWindowContainer(window, this);
	/*
	 * виджет находится в 'row' строке 'column' колонки, занимает 'rowSpan' строк и 'columnSpan' колонку
	 */
	ui->gridLayout->addWidget(container, row, column, rowSpan, columnSpan);
	/*
	 * horizontal size policy = expanding
	 * vertical size policy = preferred
	 */
	container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

/// добавление заданий
void MainWindow::addTasks()
{
	/*
	 * видимо, из-за того, что функция readJson inline, не удается нормально
	 * присвоить возвращаемое значение переменной tasks при объявлении,
	 * из-за чего объявление и присваивание разделены
	 */
	QJsonObject tasks;
	tasks = readJson(TasksPath);
	for (const auto & task : tasks) { MainWindow::tasks.emplace_back(task.toObject()); }
}

/** ********************************************* PUBLIC ********************************************* **/

MainWindow::MainWindow(QWidget * parent)
		: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	auto * view = new Qt3DExtras::Qt3DWindow(); // создаем 3д окно, на которое будут выводиться графики
	add3DWindow(view); // добавляем окно на форму
	
	graphModel = std::make_shared<GeometricProbabilityModel>(
			calculateTimeDelta(
					ui->meetFromTimeEdit->time(),
					ui->meetUntilTimeEdit->time()
			),
			ui->firstWaitingTimeSpinBox->value(),
			ui->secondWaitingTimeSpinBox->value(),
			std::make_shared<Scene>(view)
	);

	ui->planeDisplayGroupBox->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->waitingTimeLine->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->fixFirstRadioButton->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->fixSecondRadioButton->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeLabel->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeSpinBox->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeLabelMinutes->setVisible(!ui->threePersonsRadioButton->isChecked());
	
	connect(ui->updateAction, &QAction::triggered, this, &MainWindow::calculateProbability);
	connect(ui->readReferenceAction, &QAction::triggered, this, &MainWindow::showReference);
	connect(ui->meetFromTimeEdit, &QTimeEdit::timeChanged, this, &MainWindow::calculateProbability);
	connect(ui->meetUntilTimeEdit, &QTimeEdit::timeChanged, this, &MainWindow::calculateProbability);
	connect(ui->firstWaitingTimeSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateProbability);
	connect(ui->secondWaitingTimeSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateProbability);
	connect(ui->twoPersonsRadioButton, &QRadioButton::clicked, this, &MainWindow::changeAmountOfPersons);
	connect(ui->threePersonsRadioButton, &QRadioButton::clicked, this, &MainWindow::changeAmountOfPersons);
	connect(ui->probabilityPercentageSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateWaitingTime);
    connect(ui->chooseTask, &QSpinBox::valueChanged, this, &MainWindow::showTask);
    connect(ui->librarySolve, &QPushButton::pressed, this, &MainWindow::changeToTask);
    connect(ui->planeDisplayCheckBox, &QCheckBox::stateChanged, this, &MainWindow::drawPlane);

    calculateProbability(); // вычисляем вероятность для первоначальных данных
	
	addTasks();
	ui->chooseTask->setMaximum(tasks.size());
    ui->libraryTask->setText(tasks[0].task); // - Вывести первую задачу на экран
}

MainWindow::~MainWindow()
{
	delete ui;
}

/** ****************************************** PRIVATE SLOTS ***************************************** **/

/// обновление модели
void MainWindow::updateModel()
{
	// обновляем модель
	QTime timeDelta = calculateTimeDelta(ui->meetFromTimeEdit->time(), ui->meetUntilTimeEdit->time());
	graphModel->UpdateGraph(timeDelta, ui->firstWaitingTimeSpinBox->value(), ui->secondWaitingTimeSpinBox->value());

	// устанавливаем максимум и минимум интервала встречи
	ui->meetFromTimeEdit->setMaximumTime(ui->meetUntilTimeEdit->time());
	ui->meetUntilTimeEdit->setMinimumTime(ui->meetFromTimeEdit->time());

	/*
	 * Устанавливаем максимум интервала ожидания
	 *
	 * Если timeDelta равна нулю, то и на спинбоксы времени ожидания будут установлены нули,
	 * что приведет к некорректным результатам при вычислении вероятности или интервала ожидания,
	 *  если нули не убрать. Чтобы нули не убирать ручками, они просто не поступают в спинбоксы
	 */
	if (timeDelta.isNull())
	{
		int timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
		ui->firstWaitingTimeSpinBox->setMaximum(timeDeltaMinutes);
		ui->secondWaitingTimeSpinBox->setMaximum(timeDeltaMinutes);
	}
}

/// вычисление вероятности встречи на основе времени встречи и времени ожидания
void MainWindow::calculateProbability()
{
	// todo исключение, если время окончания встречи меньше времени начала встречи
	
	// разница времен начала и окончания встречи
	QTime timeDelta = calculateTimeDelta(ui->meetFromTimeEdit->time(), ui->meetUntilTimeEdit->time());
	double timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
	
	std::vector<int> waitingIntervals; // массив с интервалами ожидания для каждого участника
	if (!ui->threePersonsRadioButton->isChecked())
	{
		// для двоих персон помещаем в массив их интервалы ожидания
		waitingIntervals.emplace_back(ui->firstWaitingTimeSpinBox->value());
		waitingIntervals.emplace_back(ui->secondWaitingTimeSpinBox->value());
	}
	else
	{
		// так как все трое ждут одно время, заполняем массив тремя одинаковыми значениями
		for (int i = 0; i < 3; ++i) { waitingIntervals.emplace_back(ui->firstWaitingTimeSpinBox->value()); }
	}
	
	double probability = graphModel->CalculateProbability(timeDeltaMinutes, waitingIntervals);
	
	// блокируем отправку сигналов для того, чтобы сигналы не были приняты другими методами
	ui->probabilityPercentageSpinBox->blockSignals(true);
	ui->probabilityPercentageSpinBox->setValue(round(probability * 100));
	ui->probabilityPercentageSpinBox->blockSignals(false);
	
	updateModel();
}

/// вычисление времени ожидания на основе вероятности и времени встречи
void MainWindow::calculateWaitingTime()
{
	// todo исключение, если время окончания встречи меньше времени начала встречи
	
	// разница времен начала и окончания встречи
	QTime timeDelta = calculateTimeDelta(ui->meetFromTimeEdit->time(), ui->meetUntilTimeEdit->time());
	int timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
	
	double probability = ui->probabilityPercentageSpinBox->value() / 100.0; // вероятность встречи
	
	int unfixedWaitingTime; // незафиксированное время ожидания в минутах
	bool fixFirstWaitingTime; // зафиксировано ли первое время ожидания
	if (!ui->threePersonsRadioButton->isChecked()) // если на экране 2д режим
	{
		fixFirstWaitingTime = ui->fixFirstRadioButton->isChecked();
		int fixedWaitingTime; // зафиксированное время ожидания в минутах
		if (fixFirstWaitingTime) { fixedWaitingTime = ui->firstWaitingTimeSpinBox->value(); }
		else { fixedWaitingTime = ui->secondWaitingTimeSpinBox->value(); }
		
		unfixedWaitingTime = graphModel->CalculateWaitingTime(
				probability,
				timeDeltaMinutes,
				fixedWaitingTime
		);
	}
	else // если на экране 3д режим
	{
		fixFirstWaitingTime = false; // в 3д режиме доступно изменение только первого спинбокса интервала ожидания
		unfixedWaitingTime = graphModel->CalculateWaitingTime(
				probability,
				timeDeltaMinutes
		);
    }
	
	/*
	* блокируем отправку сигналов спинбоксом времени ожидания для того, чтобы изменение его значения
	* не приводило к вызову метода calculateProbability()
	*/
	if (fixFirstWaitingTime) // если первое время зафиксировано, то устанавливаем второе
	{
		ui->secondWaitingTimeSpinBox->blockSignals(true);
		ui->secondWaitingTimeSpinBox->setValue(unfixedWaitingTime);
		ui->secondWaitingTimeSpinBox->blockSignals(false);
	}
	else // если зафиксировано второе, устанавливаем первое
	{
		ui->firstWaitingTimeSpinBox->blockSignals(true);
		ui->firstWaitingTimeSpinBox->setValue(unfixedWaitingTime);
		ui->firstWaitingTimeSpinBox->blockSignals(false);
	}
	
    // обновляем график
    updateModel();
}

/// изменение количества персон, участвующих во встрече
void MainWindow::changeAmountOfPersons()
{
	graphModel->SwapGraphs();
	calculateProbability();

	ui->planeDisplayGroupBox->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->waitingTimeLine->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->fixFirstRadioButton->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->fixSecondRadioButton->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeLabel->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeSpinBox->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeLabelMinutes->setVisible(!ui->threePersonsRadioButton->isChecked());
}

/// вывод справки
void MainWindow::showReference()
{
    QDesktopServices::openUrl(ReferencePath);
}

/// Вывести задачу
void MainWindow::showTask()
{
    int taskNumber = ui->chooseTask->value() - 1;
    ui->libraryTask->setHtml(tasks[taskNumber].task);
}

/// Изменить параметры по задаче и вычислить
void MainWindow::changeToTask()
{
    int taskNumber = ui->chooseTask->value() - 1;

    ui->meetFromTimeEdit->setTime(tasks[taskNumber].meetFrom);
    ui->meetUntilTimeEdit->setTime(tasks[taskNumber].meetUntil);
    ui->firstWaitingTimeSpinBox->setValue(tasks[taskNumber].waitingIntervals[0]);
	
	// если в примере три человека и активен режим 2д, переключаемся на 3д
    if(tasks[taskNumber].amountOfPeople == 3 && ui->twoPersonsRadioButton->isChecked())
	{
		ui->threePersonsRadioButton->setChecked(true);
		changeAmountOfPersons();
	}
    else if(tasks[taskNumber].amountOfPeople == 2)  // если в примере два человека
	{
		// выставляем второй интервал ожидания
		ui->secondWaitingTimeSpinBox->setValue(tasks[taskNumber].waitingIntervals[1]);
		
		// и если находимся в 3д режиме, переключаемся в 2д режим
		if (ui->threePersonsRadioButton->isChecked())
		{
			ui->twoPersonsRadioButton->setChecked(true);
			changeAmountOfPersons();
		}
	}
}

/// Отрисовывает плоскости, вместо фигуры внутри куба в 3д режиме
void MainWindow::drawPlane()
{

}
