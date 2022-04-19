#ifndef APPOINTMENTPROBLEM_CONSTANTS_H
#define APPOINTMENTPROBLEM_CONSTANTS_H

#include <QString>

#ifdef DNDEBUG // если компилируем в релизе, стандартный макрос
    const QString ReferencePath("/resx/Helper/Helper.html");
	const QString TasksPath("/resx/Examples.json");
#else // если компилируем в дебаге
	const QString ReferencePath("D:/dev/AppointmentProblem/resx/Helper/Helper.html");
	const QString TasksPath("D:/dev/AppointmentProblem/resx/Examples.json");
#endif

#endif //APPOINTMENTPROBLEM_CONSTANTS_H
