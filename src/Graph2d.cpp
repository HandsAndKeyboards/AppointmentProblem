#include <tuple>

#include <QTime>

#include "Graph2d.h"
#include "Polygon.h"

/**
 * @brief формирование осей координат
 * @param timeDelta временной интервал встречи
 * @param waitingInterval интервал ожидания
 */
void Graph2d::addAxes(const QTime & timeDelta, int waitingInterval)
{
	static const float axisLen = 90;
	float timeDeltaNum = timeDelta.hour() * 60 + timeDelta.minute();
	float minutesPerUnit = timeDeltaNum / 60.0f; // количество минут в единице координат
	const QString timeDeltaStr = QString::number(timeDeltaNum);
	
	std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion> > xAxisSegmentPoints{
			std::make_tuple(
					"0",
					QVector3D(-5, -8, 0),
					QVector3D(0, 0, 0),
					QQuaternion::fromAxisAndAngle(0, 0, 1, -45)
			),
			std::make_tuple(
					QString::number(waitingInterval),
					QVector3D(waitingInterval / minutesPerUnit - 5, -8, 0),
					QVector3D(waitingInterval / minutesPerUnit, 0, 0),
					QQuaternion()
			),
			std::make_tuple(
					QString::number(60 - waitingInterval),
					QVector3D(60 - waitingInterval / minutesPerUnit - 5, -8, 0),
					QVector3D(60 - waitingInterval / minutesPerUnit, 0, 0),
					QQuaternion()
			),
			std::make_tuple(
					timeDeltaStr,
					QVector3D(58, -8, 0),
					QVector3D(60, 0, 0),
					QQuaternion()
			)
	};
	xAxis = std::make_unique<Axis>(
			QVector3D{0, 0, 0},
			QVector3D{axisLen, 0, 0},
			"x",
			xAxisSegmentPoints
	);
	
	QQuaternion yRotation = QQuaternion::fromAxisAndAngle(0, 0, 1, 90);
	std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion> > yAxisSegmentPoints{
			std::make_tuple(
					QString::number(waitingInterval),
					QVector3D(-10, waitingInterval / minutesPerUnit - 2.5f, 0),
					QVector3D(0, waitingInterval / minutesPerUnit, 0),
					yRotation
			),
			std::make_tuple(
					QString::number(waitingInterval),
					QVector3D(-10, 57.5f - waitingInterval / minutesPerUnit, 0),
					QVector3D(0, 60 - waitingInterval / minutesPerUnit, 0),
					yRotation
			),
			std::make_tuple(
					timeDeltaStr,
					QVector3D{-10, 57.5f, 0},
					QVector3D{0, 60, 0},
					yRotation
			)
	};
	yAxis = std::make_unique<Axis>(
			QVector3D{0, 0, 0},
			QVector3D{0, axisLen, 0},
			"y",
			yAxisSegmentPoints
	);
}

Graph2d::Graph2d(const QTime & timeDelta, int waitingInterval)
{
	addAxes(timeDelta, waitingInterval);
	
	std::vector<QVector3D> hexagonVertices{
			QVector3D(0, 0, 0),
			QVector3D(0, waitingInterval, 0),
			QVector3D(60 - waitingInterval, 60, 0),
			QVector3D(60, 60, 0),
			QVector3D(60, 60 - waitingInterval, 0),
			QVector3D(waitingInterval, 0, 0),
	};
	items.emplace_back(std::make_unique<Polygon>(Polygon::Triangulate(hexagonVertices), Qt::cyan));
	
	// todo заменить на Polygon
	QVector3D p1(0, 0, 0);
	QVector3D p2(60, 0, 0);
	QVector3D p3(60, 60, 0);
	QVector3D p4(0, 60, 0);
	items.push_back(std::make_unique<Line>(p1, p2, Qt::black));
	items.push_back(std::make_unique<Line>(p2, p3, Qt::black));
	items.push_back(std::make_unique<Line>(p3, p4, Qt::black));
	items.push_back(std::make_unique<Line>(p4, p1, Qt::black));

//	std::vector<QVector3D> workingRegionVertices{ // todo НЕ УДАЛЯТЬ
//			{0, 0, 0},
//			{60, 0, 0},
//			{60, 60, 0},
//			{0, 60, 0},
//	};
//	items.push_back(std::make_unique<Polygon>(workingRegionVertices));
}

void Graph2d::Render(Qt3DCore::QEntity * scene)
{
	// рендерим оси координат
	xAxis->Render(scene);
	yAxis->Render(scene);
	
	// рендерим все остальное
	for (auto & item: items) { item->Render(scene); }
}

void Graph2d::Remove(Qt3DCore::QEntity * scene)
{
	// удаляем со сцены оси координат
	xAxis->Remove(scene);
	yAxis->Remove(scene);
	
	// удаляем со сцены остальные элементы графика
	for (auto & item: items) { item->Remove(scene); }
}

void Graph2d::Update(const QTime & timeDelta, int waitingInterval, Qt3DCore::QEntity * scene)
{
	// очищаем сцену
	Remove(scene);
	items.clear();
	
	/*
	 * изменение меток на осях координат
	 */
	const float timeDeltaNum = timeDelta.hour() * 60 + timeDelta.minute();
	float minutesPerUnit = timeDeltaNum / 60.0f; // количество минут в единице координат
	const QString timeDeltaStr = QString::number(timeDeltaNum);
	std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion> > xAxisSegmentPoints{
			std::make_tuple(
					"0",
					QVector3D(-5, -8, 0),
					QVector3D(0, 0, 0),
					QQuaternion::fromAxisAndAngle(0, 0, 1, -45)
			),
			std::make_tuple(
					QString::number(waitingInterval),
					QVector3D(waitingInterval / minutesPerUnit - 5, -8, 0),
					QVector3D(waitingInterval / minutesPerUnit, 0, 0),
					QQuaternion()
			),
			std::make_tuple(
					QString::number(60 - waitingInterval),
					QVector3D(60 - waitingInterval / minutesPerUnit - 5, -8, 0),
					QVector3D(60 - waitingInterval / minutesPerUnit, 0, 0),
					QQuaternion()
			),
			std::make_tuple(
					timeDeltaStr,
					QVector3D(58, -8, 0),
					QVector3D(60, 0, 0),
					QQuaternion()
			)
	};
	xAxis->ResetSegmentPoints(xAxisSegmentPoints);
	
	QQuaternion yRotation = QQuaternion::fromAxisAndAngle(0, 0, 1, 90);
	std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion> > yAxisSegmentPoints{
			std::make_tuple(
					QString::number(waitingInterval),
					QVector3D(-10, waitingInterval / minutesPerUnit - 2.5f, 0),
					QVector3D(0, waitingInterval / minutesPerUnit, 0),
					yRotation
			),
			std::make_tuple(
					QString::number(60 - waitingInterval),
					QVector3D(-10, 57.5f - waitingInterval / minutesPerUnit, 0),
					QVector3D(0, 60 - waitingInterval / minutesPerUnit, 0),
					yRotation
			),
			std::make_tuple(
					timeDeltaStr,
					QVector3D{-10, 57.5f, 0},
					QVector3D{0, 60, 0},
					yRotation
			)
	};
	yAxis->ResetSegmentPoints(yAxisSegmentPoints);
	
	
	/*
	 * изменение шестиугольника
	 */
	std::vector<QVector3D> hexagonVertices{
			QVector3D(0, 0, 0),
			QVector3D(0, waitingInterval / minutesPerUnit, 0),
			QVector3D(60 - waitingInterval / minutesPerUnit, 60, 0),
			QVector3D(60, 60, 0),
			QVector3D(60, 60 - waitingInterval / minutesPerUnit, 0),
			QVector3D(waitingInterval / minutesPerUnit, 0, 0),
	};
	items.emplace_back(std::make_unique<Polygon>(Polygon::Triangulate(hexagonVertices), Qt::cyan));
	
	/*
	 * изменение границы рабочей области
	 */
	// todo заменить на Polygon
	QVector3D p1(0, 0, 0);
	QVector3D p2(60, 0, 0);
	QVector3D p3(60, 60, 0);
	QVector3D p4(0, 60, 0);
	items.push_back(std::make_unique<Line>(p1, p2, Qt::black));
	items.push_back(std::make_unique<Line>(p2, p3, Qt::black));
	items.push_back(std::make_unique<Line>(p3, p4, Qt::black));
	items.push_back(std::make_unique<Line>(p4, p1, Qt::black));

//	std::vector<QVector3D> workingRegionVertices{ // todo НЕ УДАЛЯТЬ
//			{0, 0, 0},
//			{60, 0, 0},
//			{60, 60, 0},
//			{0, 60, 0},
//	};
//	items.push_back(std::make_unique<Polygon>(workingRegionVertices));
	
	// выводим на сцену измененные объекты
	Render(scene);
}
