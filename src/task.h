#ifndef TASK_H
#define TASK_H

#include <QString>

class Task final
{
public:
    Task(int t, int T1, int T2, int p, QString desc);

    int waitingTime, meetingTime1, meetingTime2, amountOfPeople;
    QString Description;

private:

};

#endif // TASK_H
