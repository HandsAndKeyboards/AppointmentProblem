#include <memory>
#include <cmath>

#include "mainwindow.h"
#include "ui_mainwindow.h"

/** ******************************************** PRIVATE ********************************************* **/

inline QTime MainWindow::calculateTimeDelta(const QTime & start, const QTime & finish)
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
			ui->waitingTimeSpinBox->value(),
			std::make_shared<Scene>(view),
			std::make_shared<Scene>(view)
	
	);
	
	connect(ui->updateAction, &QAction::triggered, this, &MainWindow::calculateProbability);
	connect(ui->readReferenceAction, &QAction::triggered, this, &MainWindow::showReference);
	connect(ui->readAboutProgramAction, &QAction::triggered, this, &MainWindow::showAboutProgram);
	connect(ui->meetFromTimeEdit, &QTimeEdit::timeChanged, this, &MainWindow::calculateProbability);
	connect(ui->meetUntilTimeEdit, &QTimeEdit::timeChanged, this, &MainWindow::calculateProbability);
	connect(ui->waitingTimeSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateProbability);
	connect(ui->threePersonsCheckBox, &QCheckBox::stateChanged, this, &MainWindow::changeAmountOfPersons);
	connect(ui->probabilityPercentageSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateWaitingTime);
	
	calculateProbability(); // вычисляем вероятность для первоначальных данных
}

MainWindow::~MainWindow()
{
	delete ui;
}

/** ****************************************** PRIVATE SLOTS ***************************************** **/

/// вычисление вероятности встречи на основе времени встречи и времени ожидания
void MainWindow::calculateProbability()
{
	// todo исключение, если время окончания встречи меньше времени начала встречи

    // разница времен начала и окончания встречи
    QTime timeDelta = calculateTimeDelta(ui->meetFromTimeEdit->time(),ui->meetUntilTimeEdit->time());

    if(!ui->threePersonsCheckBox->isEnabled())
    {
        // вероятность встречи
        double probability = graphModel->CalculateProbability(timeDelta, ui->waitingTimeSpinBox->value());
	
        /*
         * блокируем отправку сигналов спинбоксом вероятности для того, чтобы изменение его значения
         * не приводило к вызову метода calculateWaitingTime()
         */
        ui->probabilityPercentageSpinBox->blockSignals(true);
        ui->probabilityPercentageSpinBox->setValue(round(probability * 100));
        ui->probabilityPercentageSpinBox->blockSignals(false);
	
        // обновляем график
        graphModel->UpdateGraph(timeDelta, ui->waitingTimeSpinBox->value());
    }
    else
    {

        graphModel->UpdateGraph(timeDelta, ui->waitingTimeSpinBox->value());
    }
}

/**
 * вычисление времени ожидания на основе вероятности и времени встречи
 * @param probability вероятность (в процентах), на основе которой вычисляется время ожидания
 */
void MainWindow::calculateWaitingTime()
{
	// todo исключение, если время окончания встречи меньше времени начала встречи

    // разница времен начала и окончания встречи
    QTime timeDelta = calculateTimeDelta(ui->meetFromTimeEdit->time(),ui->meetUntilTimeEdit->time());
	
    if (!ui->threePersonsCheckBox->isEnabled())
    {
        // время ожидания в минутах
        int waitingTime = graphModel->CalculateWaitingTime(
                timeDelta, ui->probabilityPercentageSpinBox->value() / 100.0
        );
	
        /*
        * блокируем отправку сигналов спинбоксом времени ожидания для того, чтобы изменение его значения
        * не приводило к вызову метода calculateProbability()
        */
        ui->waitingTimeSpinBox->blockSignals(true);
        ui->waitingTimeSpinBox->setValue(waitingTime);
        ui->waitingTimeSpinBox->blockSignals(false);
	
        // обновляем график
        graphModel->UpdateGraph(timeDelta, ui->waitingTimeSpinBox->value());
    }
    else
    {
        graphModel->UpdateGraph(timeDelta, ui->waitingTimeSpinBox->value());
    }
}

/**
 * @brief изменение количества персон, участвующих во встрече
 * @detail обмен местами активного и неактивного графиков
 * @param newAmount новое количество персонажей
 */
void MainWindow::changeAmountOfPersons()
{
	graphModel->SwapGraphs();
}

/// вывод справки
void MainWindow::showReference()
{

}

/// вывод окна "о программе"
void MainWindow::showAboutProgram()
{

}
