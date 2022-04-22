#include <tuple>

#include <QTime>

#include "Graph2d.h"
#include "ColoredPolygon.h"
#include "UncoloredPolygon.h"

/** ************************************************** PRIVATE ***************************************************** **/

/**
 * @brief формирование осей координат
 * @param timeDelta временной интервал встречи
 * @param firstWaitingInterval интервал ожидания
 */
void Graph2d::addAxes(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval)
{
	// длина осей координат
	static const float AXIS_LEN = NUMBER_OF_UNITS * 1.5;
	
	auto xAxisSegmentPoints = xAxisFormPoints(timeDelta, firstWaitingInterval, 0);
	xAxis = std::make_unique<Axis>(
			QVector3D{0, 0, 0},
			QVector3D{AXIS_LEN, 0, 0},
			"x",
			xAxisSegmentPoints
	);
	
	auto yAxisSegmentPoints = yAxisFormPoints(timeDelta, secondWaitingInterval, 0);
	yAxis = std::make_unique<Axis>(
			QVector3D{0, 0, 0},
			QVector3D{0, AXIS_LEN, 0},
			"y",
			yAxisSegmentPoints
	);
}

/// создание массива с делениями на OX
std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion> >
Graph2d::xAxisFormPoints(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval)
{
	float timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
	float minutesPerUnit = timeDeltaMinutes / NUMBER_OF_UNITS; // количество минут в единице координат
	const QString timeDeltaStr = QString::number(timeDeltaMinutes);
	
	std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion> > xAxisPoints{
			std::make_tuple(
					"0",
					QVector3D(-5, -8, 0),
					QVector3D(0, 0, 0),
					QQuaternion::fromAxisAndAngle(0, 0, 1, -45)
			),
			std::make_tuple(
					QString::number(firstWaitingInterval),
					QVector3D(firstWaitingInterval / minutesPerUnit - 5, -8, 0),
					QVector3D(firstWaitingInterval / minutesPerUnit, 0, 0),
					QQuaternion()
			),
			std::make_tuple(
					QString::number(timeDeltaMinutes - secondWaitingInterval),
					QVector3D(NUMBER_OF_UNITS - secondWaitingInterval / minutesPerUnit - 5, -8, 0),
					QVector3D(NUMBER_OF_UNITS - secondWaitingInterval / minutesPerUnit, 0, 0),
					QQuaternion()
			),
			std::make_tuple(
					timeDeltaStr,
					QVector3D(NUMBER_OF_UNITS - 2, -8, 0),
					QVector3D(NUMBER_OF_UNITS, 0, 0),
					QQuaternion()
			)
	};
	
	return xAxisPoints;
}

/// создание массива с делениями на OY
std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion> >
Graph2d::yAxisFormPoints(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval)
{
	float timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
	float minutesPerUnit = timeDeltaMinutes / NUMBER_OF_UNITS; // количество минут в единице координат
	const QString timeDeltaStr = QString::number(timeDeltaMinutes);
	
	QQuaternion yRotation = QQuaternion::fromAxisAndAngle(0, 0, 1, 90);
	std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion> > yAxisPoints{
			std::make_tuple(
					QString::number(secondWaitingInterval),
					QVector3D(-10, secondWaitingInterval / minutesPerUnit - 2.5f, 0),
					QVector3D(0, secondWaitingInterval / minutesPerUnit, 0),
					yRotation
			),
			std::make_tuple(
					QString::number(timeDeltaMinutes - firstWaitingInterval),
					QVector3D(-10, NUMBER_OF_UNITS - 2.5f - firstWaitingInterval / minutesPerUnit, 0),
					QVector3D(0, NUMBER_OF_UNITS - firstWaitingInterval / minutesPerUnit, 0),
					yRotation
			),
			std::make_tuple(
					timeDeltaStr,
					QVector3D{-10, NUMBER_OF_UNITS - 2.5f, 0},
					QVector3D{0, NUMBER_OF_UNITS, 0},
					yRotation
			)
	};
	
	return yAxisPoints;
}

/** *************************************************** PUBLIC ***************************************************** **/

/**
 * @brief конструирование 2д графика
 * @param timeDelta временной интервал встречи
 * @param firstWaitingInterval интервал ожидания в минутах
 */
Graph2d::Graph2d(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval)
{
	addAxes(timeDelta, firstWaitingInterval, secondWaitingInterval);
	
	const float timeDeltaNum = timeDelta.hour() * 60 + timeDelta.minute();
	float minutesPerUnit = timeDeltaNum / NUMBER_OF_UNITS; // количество минут в единице координат
	std::vector<QVector3D> hexagonVertices{
			QVector3D(0, 0, 0),
			QVector3D(0, secondWaitingInterval / minutesPerUnit, 0),
			QVector3D(NUMBER_OF_UNITS - secondWaitingInterval / minutesPerUnit, NUMBER_OF_UNITS, 0),
			QVector3D(NUMBER_OF_UNITS, NUMBER_OF_UNITS, 0),
			QVector3D(NUMBER_OF_UNITS, NUMBER_OF_UNITS - firstWaitingInterval / minutesPerUnit, 0),
			QVector3D(firstWaitingInterval / minutesPerUnit, 0, 0),
	};
	items.emplace_back(std::make_unique<ColoredPolygon>(IPolygon::Triangulate(hexagonVertices), Qt::cyan));
	
	std::vector<QVector3D> workingAreaPolygon{
			QVector3D(0, 0, 0),
			QVector3D(NUMBER_OF_UNITS, 0, 0),
			QVector3D(NUMBER_OF_UNITS, NUMBER_OF_UNITS, 0),
			QVector3D(0, NUMBER_OF_UNITS, 0)
	};
	items.emplace_back(std::make_unique<UncoloredPolygon>(workingAreaPolygon));
}

/// рендер графика на 3д сцене
void Graph2d::Render(Qt3DCore::QEntity * scene)
{
	// рендерим оси координат
	xAxis->Render(scene);
	yAxis->Render(scene);
	
	// рендерим все остальное
	for (auto & item: items) { item->Render(scene); }
}

/// удаление графика со сцены
void Graph2d::Remove()
{
	// удаляем со сцены оси координат
	xAxis->Remove();
	yAxis->Remove();
	
	// удаляем со сцены остальные элементы графика
	for (auto & item: items) { item->Remove(); }
}

/// обновление графика
void
Graph2d::Update(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval, Qt3DCore::QEntity * scene)
{
	// очищаем сцену
	Remove();
	items.clear();
	
	/*
	 * изменение меток на осях координат
	 */
	const float timeDeltaNum = timeDelta.hour() * 60 + timeDelta.minute();
	float minutesPerUnit = timeDeltaNum / NUMBER_OF_UNITS; // количество минут в единице координат
	
	auto xAxisSegmentPoints = xAxisFormPoints(timeDelta, firstWaitingInterval, secondWaitingInterval);
	xAxis->ResetSegmentPoints(xAxisSegmentPoints);

	auto yAxisSegmentPoints = yAxisFormPoints(timeDelta, firstWaitingInterval, secondWaitingInterval);
	yAxis->ResetSegmentPoints(yAxisSegmentPoints);
	
	/*
	 * изменение шестиугольника
	 */
	std::vector<QVector3D> hexagonVertices{
			QVector3D(0, 0, 0),
			QVector3D(0, secondWaitingInterval / minutesPerUnit, 0),
			QVector3D(NUMBER_OF_UNITS - secondWaitingInterval / minutesPerUnit, NUMBER_OF_UNITS, 0),
			QVector3D(NUMBER_OF_UNITS, NUMBER_OF_UNITS, 0),
			QVector3D(NUMBER_OF_UNITS, NUMBER_OF_UNITS - firstWaitingInterval / minutesPerUnit, 0),
			QVector3D(firstWaitingInterval / minutesPerUnit, 0, 0),
	};
	items.emplace_back(std::make_unique<ColoredPolygon>(ColoredPolygon::Triangulate(hexagonVertices)));

	/*
	 * изменение границы рабочей области
	 */
	std::vector<QVector3D> polygon{
			QVector3D(0, 0, 0),
			QVector3D(NUMBER_OF_UNITS, 0, 0),
			QVector3D(NUMBER_OF_UNITS, NUMBER_OF_UNITS, 0),
			QVector3D(0, NUMBER_OF_UNITS, 0)
	};
	items.emplace_back(std::make_unique<UncoloredPolygon>(polygon));
	
	// выводим на сцену измененные объекты
	Render(scene);
}
