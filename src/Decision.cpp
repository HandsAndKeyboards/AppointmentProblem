#include <QColor>
#include <QByteArray>

#include "Decision.h"
#include "ColoredPolygon.h"

/**
 * @param edgeLength = waitingInterval
 * @param cubeEdgeLen = timeDelta
 */
Decision::Decision(int edgeLength, int cubeEdgeLen)
{
	// добавляем вершины
	float minutes_per_unit = cubeEdgeLen / 60.0; // количество минут в единице координат
	
	vertices.push_back(QVector3D(0.0f, 0.0f, 0.0f));
	vertices.push_back(QVector3D(edgeLength / minutes_per_unit, 0.0f, 0.0f));
	vertices.push_back(QVector3D(edgeLength / minutes_per_unit, 0.0f, edgeLength / minutes_per_unit));
	vertices.push_back(QVector3D(edgeLength / minutes_per_unit, edgeLength / minutes_per_unit, 0.0f));
	vertices.push_back(QVector3D(0.0f, edgeLength / minutes_per_unit, 0.0f));
	vertices.push_back(QVector3D(0.0f, 0.0f, edgeLength / minutes_per_unit));
	vertices.push_back(QVector3D(0.0f, edgeLength / minutes_per_unit, edgeLength / minutes_per_unit));
	
	vertices.push_back(QVector3D(60, 60, 60));
	vertices.push_back(QVector3D(60 - edgeLength / minutes_per_unit, 60, 60));
	vertices.push_back(QVector3D(60 - edgeLength / minutes_per_unit, 60, 60 - edgeLength / minutes_per_unit));
	vertices.push_back(QVector3D(60, 60, 60 - edgeLength / minutes_per_unit));
	vertices.push_back(QVector3D(60, 60 - edgeLength / minutes_per_unit, 60 - edgeLength / minutes_per_unit));
	vertices.push_back(QVector3D(60, 60 - edgeLength / minutes_per_unit, 60));
	vertices.push_back(QVector3D(60 - edgeLength / minutes_per_unit, 60 - edgeLength / minutes_per_unit, 60));
	
	// добавляем грани
	edges.emplace_back(std::make_unique<Line>(vertices[0], vertices[1], QColor()));
	
	edges.emplace_back(std::make_unique<Line>(vertices[0], vertices[4], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[0], vertices[5], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[1], vertices[2], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[1], vertices[3], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[6], vertices[4], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[6], vertices[5], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[2], vertices[5], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[3], vertices[4], QColor()));
	
	edges.emplace_back(std::make_unique<Line>(vertices[7], vertices[8], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[7], vertices[10], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[7], vertices[12], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[10], vertices[9], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[10], vertices[11], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[13], vertices[8], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[13], vertices[12], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[9], vertices[8], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[11], vertices[12], QColor()));
	
	edges.emplace_back(std::make_unique<Line>(vertices[1], vertices[11], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[2], vertices[12], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[3], vertices[10], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[4], vertices[9], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[5], vertices[13], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[6], vertices[8], QColor()));
	
    Shading();
}

void Decision::Render(Qt3DCore::QEntity *scene)
{
     for (auto & edge : edges)
         edge->Render(scene);

     for (auto & i : shading)
         i->Render(scene);
}

void Decision::Shading()
{ // Закраска фигуры в цвет color
    // Нижний недокуб
    std::vector<QVector3D> edge1 {
        vertices[3],
        vertices[1],
        vertices[0],
        vertices[4],
        vertices[3],
        vertices[0],
    };
    std::vector<QVector3D> edge2 {
        vertices[0],
        vertices[1],
        vertices[5],
        vertices[5],
        vertices[1],
        vertices[2],
    };
    std::vector<QVector3D> edge3 {
        vertices[0],
        vertices[5],
        vertices[4],
        vertices[4],
        vertices[5],
        vertices[6],
    };
    // Средняя часть
    std::vector<QVector3D> edge4 {
        vertices[11],
        vertices[2],
        vertices[1],
        vertices[12],
        vertices[2],
        vertices[11],
    };
    std::vector<QVector3D> edge5 {
        vertices[1],
        vertices[3],
        vertices[11],
        vertices[11],
        vertices[3],
        vertices[10],
    };
    std::vector<QVector3D> edge6 {
        vertices[3],
        vertices[4],
        vertices[9],
        vertices[10],
        vertices[3],
        vertices[9],
    };
    std::vector<QVector3D> edge7 {
        vertices[4],
        vertices[6],
        vertices[8],
        vertices[4],
        vertices[8],
        vertices[9],
    };
    std::vector<QVector3D> edge8 {
        vertices[8],
        vertices[6],
        vertices[5],
        vertices[13],
        vertices[8],
        vertices[5],
    };
    std::vector<QVector3D> edge9 {
        vertices[13],
        vertices[5],
        vertices[2],
        vertices[12],
        vertices[13],
        vertices[2],
    };
    // Верхний недокуб
    std::vector<QVector3D> edge10 {
        vertices[7],
        vertices[8],
        vertices[13],
        vertices[12],
        vertices[7],
        vertices[13],
    };
    std::vector<QVector3D> edge11 {
        vertices[12],
        vertices[10],
        vertices[7],
        vertices[11],
        vertices[10],
        vertices[12],
    };
    std::vector<QVector3D> edge12 {
        vertices[10],
        vertices[8],
        vertices[7],
        vertices[9],
        vertices[8],
        vertices[10],
    };

    shading.push_back(std::make_unique<ColoredPolygon> (edge1, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge2, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge3, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge4, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge5, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge6, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge7, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge8, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge9, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge10, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge11, Qt::red));
    shading.push_back(std::make_unique<ColoredPolygon> (edge12, Qt::red));
}

void Decision::Planing(int edgeLength, int timeDelta)
{

}

void Decision::Remove()
{
    for (auto & edge : edges) {
        edge->Remove();
    }
	
    for (auto & i : shading) {
        i->Remove(); }
}
