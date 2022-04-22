#include <vector>

#include "task.h"
#include "common/json.h"

/**
 * @brief конструирование объект
 * @param meetFrom начало интервала встречи
 * @param meetUntil окончание интервала встречи
 * @param amountOfPeople количество участников встречи
 * @param firstWaitingInterval первый интервал ожидания
 * @param secondWaitingInterval второй интервал ожидания
 * @param task текст задачи
 */
Task::Task(
		const QTime & meetFrom,
		const QTime & meetUntil,
		int amountOfPeople,
		const std::vector<int> & waitingIntervals,
		const QString & task
)
{
	construct(meetFrom, meetUntil, amountOfPeople, waitingIntervals, task);
}

/**
 * @brief конструирование объекта из json-объекта
 * @param json json-объект с необходимыми данными
 */
Task::Task(const QJsonObject & json)
{
	QJsonArray meetFromArray = json.find("meetFrom")->toArray();
	QTime meetFrom = QTime(meetFromArray[0].toInt(), meetFromArray[1].toInt());
	
	QJsonArray meetUntilArray = json.find("meetUntil")->toArray();
	QTime meetUntil = QTime(meetUntilArray[0].toInt(), meetUntilArray[1].toInt());
	
	int amountOfPeople = json.find("amountOfPeople")->toInt();
	
	QJsonArray waitingIntervalsArray = json.find("waitingIntervals")->toArray();
	std::vector<int> waitingIntervals;
	for (const auto & interval : waitingIntervalsArray) { waitingIntervals.emplace_back(interval.toInt()); }
	
	QString task = json.find("task")->toString();
	
	construct(meetFrom, meetUntil, amountOfPeople, waitingIntervals, task);
}

/**
 * @param meetFrom начало интервала встречи
 * @param meetUntil окончание интервала встречи
 * @param amountOfPeople количество участников встречи
 * @param firstWaitingInterval первый интервал ожидания
 * @param secondWaitingInterval второй интервал ожидания
 * @param task текст задачи
 */
void Task::construct(
		const QTime & meetFrom,
		const QTime & meetUntil,
		int amountOfPeople,
		const std::vector<int> & waitingIntervals,
		const QString & task
)
{
	Task::meetFrom = meetFrom;
	Task::meetUntil = meetUntil;
	Task::amountOfPeople = amountOfPeople;
	Task::waitingIntervals = waitingIntervals;
	Task::task = task;
}
