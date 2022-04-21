#ifndef APPOINTMENTPROBLEM_JSON_H
#define APPOINTMENTPROBLEM_JSON_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

/// чтение данных из json файла
inline QJsonObject readJson(const QString & filename)
{
	QFile file(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	
	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();
	
	return doc.object();
}

/// запись данных в json файл
inline void writeJson(const QJsonObject & obj, const QString & filename)
{
	QFile file(filename);
	
	file.write(QJsonDocument(obj).toJson());
	file.close();
}

#endif //APPOINTMENTPROBLEM_JSON_H
