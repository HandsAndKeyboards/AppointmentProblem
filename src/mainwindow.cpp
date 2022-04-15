#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "common/mathematicFuncs.h" // TODO УДАЛИТЬ КОСТЫЛЬ А ТО ПО ЖОПЕ

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
	
    // - Создаём задачки
       Task firstTask(15, 9, 10, 2,
                        "Два человека договорились  о встрече  между 9  и  10  часами  "
                        "утра.  Пришедший  первым  ждет  второго  в  течение  15  мин,  "
                        "после  чего  уходит   (если  не  встретились).   Найти  "
                        "вероятность  того,  что  встреча  состоится,  если  каждый  "
                        "наудачу  выбирает момент своего прихода."),
            secondTask(20, 19, 20, 2,
                       "Два лица A и B условились встретиться в определенном "
                       "месте между 7 и 8 часами вечера, причем тот, кто "
                       "приходит первым, ждет другого 20 минут, после уходит. "
                       "Чему равна вероятность их встречи, если моменты их "
                       "прихода случайны и независимы друг от друга?"),
            thirdTask(5, 12, 13, 2,
                      "Какова вероятность Вашей встречи с другом, если вы "
                      "договорились встретиться в определенном месте, с 12.00 "
                      "до 13.00 часов и ждете друг друга в течение 5 минут?"),
            fourthTask(10, 7, 8, 3,
                       "Три человека договорились встретиться в течение определенного "
                       " часа, тот, кто приходит первым, ждет 10 мин, а потом уходит. "
                       " Найти вероятность, что встреча состоялась.");
    Tasks.push_back(firstTask);
    Tasks.push_back(secondTask);
    Tasks.push_back(thirdTask);
    Tasks.push_back(fourthTask);

	ui->planeDisplayGroupBox->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->waitingTimeLine->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->fixFirstRadioButton->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->fixSecondRadioButton->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeLabel->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeSpinBox->setVisible(!ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeLabelMinutes->setVisible(!ui->threePersonsRadioButton->isChecked());
	
	connect(ui->updateAction, &QAction::triggered, this, &MainWindow::calculateProbability);
	connect(ui->readReferenceAction, &QAction::triggered, this, &MainWindow::showReference);
	connect(ui->readAboutProgramAction, &QAction::triggered, this, &MainWindow::showAboutProgram);
	connect(ui->meetFromTimeEdit, &QTimeEdit::timeChanged, this, &MainWindow::calculateProbability);
	connect(ui->meetUntilTimeEdit, &QTimeEdit::timeChanged, this, &MainWindow::calculateProbability);
	connect(ui->firstWaitingTimeSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateProbability);
	connect(ui->secondWaitingTimeSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateProbability);
	connect(ui->twoPersonsRadioButton, &QRadioButton::clicked, this, &MainWindow::changeAmountOfPersons);
	connect(ui->threePersonsRadioButton, &QRadioButton::clicked, this, &MainWindow::changeAmountOfPersons);
	connect(ui->probabilityPercentageSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateWaitingTime);
    connect(ui->chooseTask, &QSpinBox::valueChanged, this, &MainWindow::showTask);
    connect(ui->librarySolve, &QPushButton::pressed, this, &MainWindow::changeToTask);

    calculateProbability(); // вычисляем вероятность для первоначальных данных
    ui->libraryTask->setText(Tasks[0].Description); // - Вывести первую задачу на экран
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

	if (!ui->threePersonsRadioButton->isChecked())
	{
		// вероятность встречи
		double probability = graphModel->CalculateProbability(
				timeDelta,
				ui->firstWaitingTimeSpinBox->value(),
				ui->secondWaitingTimeSpinBox->value()
		);

		/*
		 * блокируем отправку сигналов спинбоксом вероятности для того, чтобы изменение его значения
		 * не приводило к вызову метода calculateWaitingTime()
		 */
		ui->probabilityPercentageSpinBox->blockSignals(true);
		ui->probabilityPercentageSpinBox->setValue(round(probability * 100));
		ui->probabilityPercentageSpinBox->blockSignals(false);

		// обновляем график
        updateModel();
	}
	else
	{
		// todo УДАЛИТЬ КОСТЫЛЬ А ТО ПО ЖОПЕ
		double timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
		double waitingInterval = ui->firstWaitingTimeSpinBox->value() / timeDeltaMinutes;
		double probability = 3 * pow(waitingInterval, 2) - 2 * pow(waitingInterval, 3);

		ui->probabilityPercentageSpinBox->blockSignals(true);
		ui->probabilityPercentageSpinBox->setValue(round(probability * 100));
		ui->probabilityPercentageSpinBox->blockSignals(false);
		// todo УДАЛИТЬ КОСТЫЛЬ А ТО ПО ЖОПЕ

		// обновляем график
		graphModel->UpdateGraph(timeDelta, ui->firstWaitingTimeSpinBox->value(), 0);
	}
}

/// вычисление времени ожидания на основе вероятности и времени встречи
void MainWindow::calculateWaitingTime()
{
	// todo исключение, если время окончания встречи меньше времени начала встречи
	
	// разница времен начала и окончания встречи
	QTime timeDelta = calculateTimeDelta(ui->meetFromTimeEdit->time(), ui->meetUntilTimeEdit->time());
	
	if (!ui->threePersonsRadioButton->isChecked())
	{
		bool fixFirstWaitingTime = ui->fixFirstRadioButton->isChecked(); // зафиксированное первое время ожидания
		int fixedWaitingTime; // зафиксированное время ожидания в минутах
		if (fixFirstWaitingTime) { fixedWaitingTime = ui->firstWaitingTimeSpinBox->value(); }
		else { fixedWaitingTime = ui->secondWaitingTimeSpinBox->value(); }

		// незафиксированное время ожидания в минутах
		int unfixedWaitingTime = graphModel->CalculateWaitingTime(
				timeDelta,
				ui->probabilityPercentageSpinBox->value() / 100.0,
				fixedWaitingTime
		);

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
	}
	else
	{
		// TODO УДАЛИТЬ КОСТЫЛЬ А ТО ПО ЖОПЕ
		int timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
		double probability = ui->probabilityPercentageSpinBox->value() / 100.0;
		std::array<double, 3> solution = solveCubic(2, -3, 0, probability);

		ui->firstWaitingTimeSpinBox->blockSignals(true);
		ui->firstWaitingTimeSpinBox->setValue(round(timeDeltaMinutes * solution[2]));
		ui->firstWaitingTimeSpinBox->blockSignals(false);
		// TODO УДАЛИТЬ КОСТЫЛЬ А ТО ПО ЖОПЕ
    }
    // обновляем график
    updateModel();
}

/// изменение количества персон, участвующих во встрече
void MainWindow::changeAmountOfPersons()
{
	graphModel->SwapGraphs();
	
	// todo УДАЛИТЬ КОСТЫЛЬ А ТО ПО ЖОПЕ
	QTime timeDelta = calculateTimeDelta(ui->meetFromTimeEdit->time(), ui->meetUntilTimeEdit->time());
	if (ui->threePersonsRadioButton->isChecked())
	{
		double timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
		double waitingInterval = ui->firstWaitingTimeSpinBox->value() / timeDeltaMinutes;
		double probability = 3 * pow(waitingInterval, 2) - 2 * pow(waitingInterval, 3);

		ui->probabilityPercentageSpinBox->blockSignals(true);
		ui->probabilityPercentageSpinBox->setValue(round(probability * 100));
		ui->probabilityPercentageSpinBox->blockSignals(false);

//		graphModel->UpdateGraph(timeDelta, ui->firstWaitingTimeSpinBox->value(), 0);
	}
	else
	{
		// вероятность встречи
		double probability = graphModel->CalculateProbability(
				timeDelta,
				ui->firstWaitingTimeSpinBox->value(),
				ui->secondWaitingTimeSpinBox->value()
		);

		/*
		 * блокируем отправку сигналов спинбоксом вероятности для того, чтобы изменение его значения
		 * не приводило к вызову метода calculateWaitingTime()
		 */
		ui->probabilityPercentageSpinBox->blockSignals(true);
		ui->probabilityPercentageSpinBox->setValue(round(probability * 100));
		ui->probabilityPercentageSpinBox->blockSignals(false);

		// обновляем график
//		graphModel->UpdateGraph(timeDelta, ui->firstWaitingTimeSpinBox->value(), ui->secondWaitingTimeSpinBox->value());
	}
    updateModel();
	// todo УДАЛИТЬ КОСТЫЛЬ А ТО ПО ЖОПЕ

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
    QDesktopServices::openUrl(QUrl("file:///" + QCoreApplication::applicationDirPath() + "/Helper.html"));
}

/// вывод окна "о программе"
void MainWindow::showAboutProgram()
{

}

// - Вывод задачи
void MainWindow::showTask()
{
    int taskNumber = ui->chooseTask->value() - 1;
    ui->libraryTask->setText(Tasks[taskNumber].Description);
}

void MainWindow::changeToTask()
{
    int taskNumber = ui->chooseTask->value() - 1;
    QTime meetingTime1(Tasks[taskNumber].meetingTime1, 0), meetingTime2(Tasks[taskNumber].meetingTime2, 0);

    ui->meetFromTimeEdit->setTime(meetingTime1);
    ui->meetUntilTimeEdit->setTime(meetingTime2);
    ui->firstWaitingTimeSpinBox->setValue(Tasks[taskNumber].waitingTime);

    if(Tasks[taskNumber].amountOfPeople == 3 && !ui->threePersonsRadioButton->isChecked()) { ui->threePersonsRadioButton->setChecked(true); changeAmountOfPersons();  }
    else if(ui->threePersonsRadioButton->isChecked()) { ui->twoPersonsRadioButton->setChecked(true); changeAmountOfPersons();  }
}
