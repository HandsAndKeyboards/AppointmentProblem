#include <memory>
#include <cmath>

#include "mainwindow.h"
#include "ui_mainwindow.h"

/** ******************************************** PRIVATE ********************************************* **/

QTime MainWindow::calculateTimeDelta(const QTime & start, const QTime & finish)
{
	return QTime::fromMSecsSinceStartOfDay(start.msecsTo(finish));
}

/** ********************************************* PUBLIC ********************************************* **/

MainWindow::MainWindow(QWidget * parent)
		: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	graphModel = std::make_shared<GeometricProbabilityModel>(
			calculateTimeDelta(
					ui->meetFromTimeEdit->time(),
					ui->meetUntilTimeEdit->time()
			),
			ui->waitingTimeSpinBox->value()
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

/// добавление 3Д окна на форму
void MainWindow::Add3DWindow(Qt3DExtras::Qt3DWindow * window, int row, int column, int rowSpan, int columnSpan)
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

/** ****************************************** PRIVATE SLOTS ***************************************** **/

/// вычисление вероятности встречи на основе времени встречи и времени ожидания
void MainWindow::calculateProbability()
{
	// todo исключение, если время окончания встречи меньше времени начала встречи
	
	// разница времен начала и окончания встречи
	QTime timeDelta = calculateTimeDelta(ui->meetFromTimeEdit->time(),ui->meetUntilTimeEdit->time());
	// вероятность встречи
	double probability = graphModel->CalculateProbability(timeDelta, ui->waitingTimeSpinBox->value());
	
	/*
	 * блокируем отправку сигналов спинбоксом вероятности для того, чтобы изменение его значения
	 * не приводило к вызову метода calculateWaitingTime()
	 */
	ui->probabilityPercentageSpinBox->blockSignals(true);
	ui->probabilityPercentageSpinBox->setValue(round(probability * 100));
	ui->probabilityPercentageSpinBox->blockSignals(false);
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
}

/**
 * изменение количества персон, участвующих во встрече
 * @param newAmount новое количество персонажей
 */
void MainWindow::changeAmountOfPersons(int newAmount)
{

}

/// вывод справки
void MainWindow::showReference()
{

}

/// вывод окна "о программе"
void MainWindow::showAboutProgram()
{

}