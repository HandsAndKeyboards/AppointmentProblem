#ifndef TASK_H
#define TASK_H

#include <QJsonObject>
#include <QString>

struct Task final
{
	/**
	 * @brief конструирует объект
	 * @param meetFrom начало интервала встречи
	 * @param meetUntil окончание интервала встречи
	 * @param amountOfPeople количество участников встречи
	 * @param firstWaitingInterval первый интервал ожидания
	 * @param secondWaitingInterval второй интервал ожидания
	 * @param task текст задачи
	 */
	Task(const QTime & meetFrom,
	     const QTime & meetUntil,
	     int amountOfPeople,
		 const std::vector<int> & waitingIntervals,
	     const QString & task);
	
	/**
	 * @brief конструирование объекта из json-объекта
	 * @param json json-объект с необходимыми данными
	 */
	explicit Task(const QJsonObject & json);
	
	QTime meetFrom; ///< начало интервала встречи
	QTime meetUntil; ///< окончание интервала встречи
	int amountOfPeople; ///< количество участников встречи
	std::vector<int> waitingIntervals; ///< интервалы ожидания
	QString task; ///< текст задачи

private:
	/**
	 * @param meetFrom начало интервала встречи
	 * @param meetUntil окончание интервала встречи
	 * @param amountOfPeople количество участников встречи
	 * @param firstWaitingInterval первый интервал ожидания
	 * @param secondWaitingInterval второй интервал ожидания
	 * @param task текст задачи
	 */
	void construct(const QTime & meetFrom,
	               const QTime & meetUntil,
	               int amountOfPeople,
	               const std::vector<int> & waitingIntervals,
	               const QString & task);
};

#endif // TASK_H
