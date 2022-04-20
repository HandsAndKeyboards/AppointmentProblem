#ifndef APPOINTMENTPROBLEM_JSON_H
#define APPOINTMENTPROBLEM_JSON_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

//#include "Error.h" // todo сделать систему исключений

/// чтение данных из json файла
inline QJsonObject readJson(const QString & filename)
{
	QFile file(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
//	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//	{
//		throw FileError("не удалось прочитать файл " + filename.toStdString());
//	}
	
	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();
	
	return doc.object();
}

/// запись данных в json файл
inline void writeJson(const QJsonObject & obj, const QString & filename)
{
	QFile file(filename);
//	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
//	{
//		throw FileError("не удалось записать в файл " + filename.toStdString());
//	}
	
	file.write(QJsonDocument(obj).toJson());
	file.close();
}

#endif //APPOINTMENTPROBLEM_JSON_H
