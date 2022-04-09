#include <tuple>

#include <QTime>

#include "Graph2d.h"

void Graph2d::addAxes(const QTime & timeDelta, int waitingInterval)
{
	const QString timeDeltaStr = timeDelta.toString("hh:mm");
	
	std::list< std::tuple<QString, QVector3D, QVector3D, QQuaternion> > xAxisSegmentPoints {
		std::make_tuple("00:00", QVector3D{-3, -6, 0}, QVector3D{0, 0, 0}, QQuaternion::fromAxisAndAngle(0, 0, 1, -45)),
		std::make_tuple(timeDeltaStr, QVector3D{8, -6, 0}, QVector3D{10, 0, 0}, QQuaternion())
	};
	xAxis = std::make_unique<Axis>(
			QVector3D{0, 0, 0},
			QVector3D{20, 0, 0},
			"x",
			xAxisSegmentPoints
	);
	
	QQuaternion yRotation = QQuaternion::fromAxisAndAngle(0, 0, 1, 90);
	std::list< std::tuple<QString, QVector3D, QVector3D, QQuaternion> > yAxisSegmentPoints {
		std::make_tuple(timeDeltaStr, QVector3D{-5, 6, 0}, QVector3D{0, 10, 0}, yRotation)
	};
	yAxis = std::make_unique<Axis>(
			QVector3D{0, 0, 0},
			QVector3D{0, 20, 0},
			"y",
			yAxisSegmentPoints
	);
	
	// remove
	std::list< std::tuple<QString, QVector3D, QVector3D, QQuaternion> > zAxisSegmentPoints;
	zAxis = std::make_unique<Axis>(
			QVector3D{0, 0, 0},
			QVector3D{0, 0, 20},
			"z",
			zAxisSegmentPoints
	);
	// remove
}

Graph2d::Graph2d(const QTime & timeDelta, int waitingInterval)
{
	addAxes(timeDelta, waitingInterval);
	
	QVector3D p1(0, 0, 0);
	QVector3D p2(10, 0, 0);
	QVector3D p3(10, 10, 0);
	QVector3D p4(0, 10, 0);
	QVector3D p5(0, 0, 10);
	QVector3D p6(10, 0, 10);
	QVector3D p7(10, 10, 10);
	QVector3D p8(0, 10, 10);
	items.push_back(std::make_unique<Line>(p1, p2, Qt::black));
	items.push_back(std::make_unique<Line>(p2, p3, Qt::black));
	items.push_back(std::make_unique<Line>(p3, p4, Qt::black));
	items.push_back(std::make_unique<Line>(p4, p1, Qt::black));
	items.push_back(std::make_unique<Line>(p5, p6, Qt::black));
	items.push_back(std::make_unique<Line>(p6, p7, Qt::black));
	items.push_back(std::make_unique<Line>(p7, p8, Qt::black));
	items.push_back(std::make_unique<Line>(p8, p5, Qt::black));
	items.push_back(std::make_unique<Line>(p1, p5, Qt::black));
	items.push_back(std::make_unique<Line>(p2, p6, Qt::black));
	items.push_back(std::make_unique<Line>(p3, p7, Qt::black));
	items.push_back(std::make_unique<Line>(p4, p8, Qt::black));
}

Graph2d::~Graph2d()
{

}

void Graph2d::Render(Qt3DCore::QEntity * scene)
{
	// рендерим оси координат
	xAxis->Render(scene);
	yAxis->Render(scene);
	if (zAxis) zAxis->Render(scene); // debug
	
	// рендерим все остальное
	for (auto & item : items) { item->Render(scene); }
}

void Graph2d::Remove(Qt3DCore::QEntity * scene)
{
	// удаляем со сцены оси координат
	xAxis->Remove(scene);
	yAxis->Remove(scene);
	
	// удаляем со сцены остальные элементы графика
	for (auto & item : items) { item->Remove(scene); }
}

void Graph2d::Update(const QTime & timeDelta, int waitingInterval)
{

}
