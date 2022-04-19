#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt3DExtras/Qt3DWindow>
#include <QDesktopServices>

#include "GeometricProbabilityModel.h"
#include "task.h"

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
	QWidget * container; ///< является контейнером для окна Qt3DWindow
    QVector<Task> Tasks; // - Задачи

	QTime calculateTimeDelta(const QTime & start, const QTime & finish);
	
	/// добавление 3Д окна на форму
	void add3DWindow(Qt3DExtras::Qt3DWindow * window, int row = 0, int column = 2, int rowSpan = 5, int columnSpan = 1);

private slots:
	/// вычисление вероятности встречи на основе времени встречи и времени ожидания
	void calculateProbability();

	/// вычисление времени ожидания на основе вероятности и времени встречи
	void calculateWaitingTime();

	/// изменение количества персон, участвующих во встрече
	void changeAmountOfPersons();
	
	/// вывод справки
	void showReference();
	
	/// вывод окна "о программе"
	void showAboutProgram();
	
    // - Вывести задачу
    void showTask();

    // - Изменить параметры по задаче и вычислить
    void changeToTask();

    // - Отрисовывает плоскости, вместо фигуры внутри куба в 3д режиме
    void changeModeDecision(int mode);
};

#endif // MAINWINDOW_H
