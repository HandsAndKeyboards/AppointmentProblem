#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "GeometricProbabilityModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	MainWindow(QWidget * parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow * ui;
	std::shared_ptr<GeometricProbabilityModel> graphModel;
	
	QTime calculateTimeDelta(const QTime & start, const QTime & finish);

private slots:
	/// вычисление вероятности встречи на основе времени встречи и времени ожидания
	void calculateProbability();

	/**
	 * вычисление времени ожидания на основе вероятности и времени встречи
	 * @param probability вероятность (в процентах), на основе которой вычисляется время ожидания
	 */
	void calculateWaitingTime();

	/**
	 * изменение количества персон, участвующих во встрече
	 * @param newAmount новое количество персонажей
	 */
	void changeAmountOfPersons(int newAmount);
	
	/// вывод справки
	void showReference();
	
	/// вывод окна "о программе"
	void showAboutProgram();
};

#endif // MAINWINDOW_H
