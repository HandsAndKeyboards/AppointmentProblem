#include "mainwindow.h"
#include "ui_mainwindow.h"

/** ******************************************** PRIVATE ********************************************* **/

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
	
	ui->planeDisplayGroupBox->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeLabel->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeSpinBox->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeLabelMinutes->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->fixSecondRadioButton->setVisible(ui->threePersonsRadioButton->isChecked());
	
	connect(ui->updateAction, &QAction::triggered, this, &MainWindow::calculateProbability);
	connect(ui->readReferenceAction, &QAction::triggered, this, &MainWindow::showReference);
	connect(ui->showExamplesAction, &QAction::triggered, this, &MainWindow::showExamplesLibrary);
	connect(ui->readAboutProgramAction, &QAction::triggered, this, &MainWindow::showAboutProgram);
	connect(ui->meetFromTimeEdit, &QTimeEdit::timeChanged, this, &MainWindow::calculateProbability);
	connect(ui->meetUntilTimeEdit, &QTimeEdit::timeChanged, this, &MainWindow::calculateProbability);
	connect(ui->firstWaitingTimeSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateProbability);
	connect(ui->secondWaitingTimeSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateProbability);
	connect(ui->twoPersonsRadioButton, &QRadioButton::clicked, this, &MainWindow::changeAmountOfPersons);
	connect(ui->threePersonsRadioButton, &QRadioButton::clicked, this, &MainWindow::changeAmountOfPersons);
	connect(ui->probabilityPercentageSpinBox, &QSpinBox::valueChanged, this, &MainWindow::calculateWaitingTime);
//	connect(ui->planeDisplayCheckBox, QCheckBox::stateChanged, this, ); // todo связать с чем-то
}

MainWindow::~MainWindow()
{
	delete ui;
}

/** ****************************************** PRIVATE SLOTS ***************************************** **/

/// вычисление вероятности встречи на основе времени встречи и времени ожидания
void MainWindow::calculateProbability()
{

}

/// вычисление времени ожидания на основе вероятности и времени встречи
void MainWindow::calculateWaitingTime()
{

}

/// изменение количества персон, участвующих во встрече
void MainWindow::changeAmountOfPersons()
{
	ui->planeDisplayGroupBox->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeLabel->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeSpinBox->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->secondWaitingTimeLabelMinutes->setVisible(ui->threePersonsRadioButton->isChecked());
	ui->fixSecondRadioButton->setVisible(ui->threePersonsRadioButton->isChecked());
}

/// вывод справки
void MainWindow::showReference()
{

}

/// вывод окна "о программе"
void MainWindow::showAboutProgram()
{

}

/// вывод библиотеки примеров
void MainWindow::showExamplesLibrary()
{

}
