#include <tuple>
#include <QTime>

#include "Graph3d.h"
#include "Decision.h"

void Graph3d::createAxes(const QTime &timeDelta, int waitingInterval)
{
    float axisLength = 90;
    const QString timeDeltaStr = QString::number(timeDelta.hour() * 60 + timeDelta.minute());

    std::list< std::tuple<QString, QVector3D, QVector3D, QQuaternion> > xAxisSegmentPoints {
        std::make_tuple("0", QVector3D{-5, -8, 0}, QVector3D{0, 0, 0}, QQuaternion()),
        std::make_tuple(timeDeltaStr, QVector3D{58, -8, 0}, QVector3D{60, 0, 0}, QQuaternion())
    };
    xAxis = std::make_unique<Axis>(
            QVector3D{0, 0, 0},
            QVector3D{axisLength, 0, 0},
            "x",
            xAxisSegmentPoints
    );

    std::list< std::tuple<QString, QVector3D, QVector3D, QQuaternion> > yAxisSegmentPoints {
        std::make_tuple(timeDeltaStr, QVector3D{-8, 58, 0}, QVector3D{0, 60, 0}, QQuaternion())
    };
    yAxis = std::make_unique<Axis>(
            QVector3D{0, 0, 0},
            QVector3D{0, axisLength, 0},
            "y",
            yAxisSegmentPoints
    );

    std::list< std::tuple<QString, QVector3D, QVector3D, QQuaternion> > zAxisSegmentPoints{
        std::make_tuple(timeDeltaStr, QVector3D{-8, 0, 58}, QVector3D{0, 0, 60}, QQuaternion())
    };
    zAxis = std::make_unique<Axis>(
            QVector3D{0, 0, 0},
            QVector3D{0, 0, axisLength},
            "z",
            zAxisSegmentPoints
                );
}

void Graph3d::createItems(const QTime &timeDelta, int waitingInterval)
{
    items.push_back(std::make_unique<Cube>(60));
    items.push_back(std::make_unique<Decision>(
                        waitingInterval,
                        60
                        )
    );
}

Graph3d::Graph3d(const QTime & timeDelta, int waitingInterval)
{
    createAxes(timeDelta, waitingInterval);
    createItems(timeDelta, waitingInterval);
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
    // Удаляем со сцены оси координат
    xAxis->Remove(scene);
    yAxis->Remove(scene);
    zAxis->Remove(scene);

    // Удаляем элементы
    for (auto & item : items) { item->Remove(scene); }
}

void Graph3d::Update(const QTime &timeDelta, int waitingInterval, Qt3DCore::QEntity *scene)
{
    Remove(scene);
    items.clear();
    createAxes(timeDelta, waitingInterval);
    createItems(timeDelta, waitingInterval);
    Render(scene);
}
