#include "task.h"

Task::Task(int t, int T1, int T2, int p, QString desc)
{
    waitingTime = t;
    meetingTime1 = T1;
    meetingTime2 = T2;
    amountOfPeople = p;
    Description = desc;
}
