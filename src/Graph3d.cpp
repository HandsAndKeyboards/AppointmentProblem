#include <tuple>
#include <QTime>

#include "Graph3d.h"
#include "Decision.h"

void Graph3d::createAxes(const QTime &timeDelta, int waitingInterval)
{
    const QString timeDeltaStr = timeDelta.toString("mm");
    float axisLength = timeDelta.hour() * 60 + timeDelta.minute() + 30;

    std::list< std::tuple<QString, QVector3D, QVector3D, QQuaternion> > xAxisSegmentPoints {
        std::make_tuple("0", QVector3D{-3, -6, 0}, QVector3D{0, 0, 0}, QQuaternion::fromAxisAndAngle(0, 0, 1, -45)),
        std::make_tuple(timeDeltaStr, QVector3D{8, -6, 0}, QVector3D{10, 0, 0}, QQuaternion())
    };
    xAxis = std::make_unique<Axis>(
            QVector3D{0, 0, 0},
            QVector3D{axisLength, 0, 0},
            "x",
            xAxisSegmentPoints
    );

    QQuaternion yRotation = QQuaternion::fromAxisAndAngle(0, 0, 1, 90);
    std::list< std::tuple<QString, QVector3D, QVector3D, QQuaternion> > yAxisSegmentPoints {
        std::make_tuple(timeDeltaStr, QVector3D{-5, 6, 0}, QVector3D{0, 10, 0}, yRotation)
    };
    yAxis = std::make_unique<Axis>(
            QVector3D{0, 0, 0},
            QVector3D{0, axisLength, 0},
            "y",
            yAxisSegmentPoints
    );

    // remove
    std::list< std::tuple<QString, QVector3D, QVector3D, QQuaternion> > zAxisSegmentPoints;
    zAxis = std::make_unique<Axis>(
            QVector3D{0, 0, 0},
            QVector3D{0, 0, axisLength},
            "z",
            zAxisSegmentPoints
    );
}

Graph3d::Graph3d(const QTime & timeDelta, int waitingInterval)
{
    createAxes(timeDelta, waitingInterval);

    items.push_back(std::make_unique<Cube>(timeDelta.hour() * 60 + timeDelta.minute()));
    items.push_back(std::make_unique<Decision>(
                        waitingInterval,
                        timeDelta.hour() * 60 + timeDelta.minute()
                        )
    );
}

Graph3d::~Graph3d()
{

}

void Graph3d::Render(Qt3DCore::QEntity *scene)
{
    // Рендерим оси
    xAxis->Render(scene);
    yAxis->Render(scene);
    zAxis->Render(scene);

    // Рендерим элементы графа
    for (auto & item : items) { item->Render(scene); }
}

void Graph3d::Remove(Qt3DCore::QEntity *scene)
{

}

void Graph3d::Update(const QTime &timeDelta, int waitingInterval)
{

}
