#include <QColor>
#include <QByteArray>

#include "Decision.h"
#include "ColoredPolygon.h"

/**
 * @param edgeLength = waitingInterval
 * @param cubeEdgeLen = timeDelta
 */
Decision::Decision(int edgeLength, int cubeEdgeLen, bool mode)
{
    this->mode = mode;

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
    Planing();
}

void Decision::Render(Qt3DCore::QEntity *scene)
{
     for (auto & i : edges)
         i->Render(scene);

     if (mode)
     {
         for (auto & i : planing)
             i->Render(scene);
     }
     else
     {
         for (auto & i : shading)
             i->Render(scene);
     }
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

    shading.push_back(std::make_unique<ColoredPolygon> (edge1, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge2, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge3, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge4, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge5, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge6, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge7, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge8, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge9, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge10, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge11, QColor(170, 0, 0)));
    shading.push_back(std::make_unique<ColoredPolygon> (edge12, QColor(170, 0, 0)));
}

void Decision::Planing()
{
    QVector3D temp1; // Для хранения копии вершины
    QVector3D temp2; // Для хранения копии вершины

    // Основные плоскости
    temp1 = vertices[1]; temp1.setZ(60);
    temp2 = vertices[12]; temp2.setZ(0);
    std::vector<QVector3D> plane4 {
        vertices[1],
        temp1,
        vertices[12],
        vertices[12],
        vertices[1],
        temp2,
    };
    std::vector<QVector3D> plane5 {
        vertices[12],
        temp1,
        vertices[1],
        temp2,
        vertices[1],
        vertices[12],
    };

    temp1 = vertices[1]; temp1.setY(60);
    temp2 = vertices[10]; temp2.setY(0);
    std::vector<QVector3D> plane6 {
        vertices[1],
        temp1,
        vertices[10],
        temp2,
        vertices[10],
        vertices[1],
    };
    std::vector<QVector3D> plane7 {
        vertices[10],
        temp1,
        vertices[1],
        temp2,
        vertices[1],
        vertices[10],
    };

    temp1 = vertices[4]; temp1.setX(60);
    temp2 = vertices[10]; temp2.setX(0);
    std::vector<QVector3D> plane8 {
        vertices[4],
        temp1,
        vertices[10],
        temp2,
        vertices[10],
        vertices[4],
    };
    std::vector<QVector3D> plane9 {
        vertices[10],
        temp1,
        vertices[4],
        temp2,
        vertices[4],
        vertices[10],
    };

    temp1 = vertices[4]; temp1.setZ(60);
    temp2 = vertices[8]; temp2.setZ(0);
    std::vector<QVector3D> plane10 {
        vertices[4],
        temp1,
        vertices[8],
        temp2,
        vertices[8],
        vertices[4],
    };
    std::vector<QVector3D> plane11 {
        vertices[8],
        temp1,
        vertices[4],
        temp2,
        vertices[4],
        vertices[8],
    };

    temp1 = vertices[5]; temp1.setY(60);
    temp2 = vertices[8]; temp2.setY(0);
    std::vector<QVector3D> plane12 {
        vertices[5],
        temp1,
        vertices[8],
        temp2,
        vertices[8],
        vertices[5],
    };
    std::vector<QVector3D> plane13 {
        vertices[8],
        temp1,
        vertices[5],
        temp2,
        vertices[5],
        vertices[8],
    };

    temp1 = vertices[5]; temp1.setX(60);
    temp2 = vertices[12]; temp2.setX(0);
    std::vector<QVector3D> plane14 {
        vertices[5],
        temp1,
        vertices[12],
        temp2,
        vertices[12],
        vertices[5],
    };
    std::vector<QVector3D> plane15 {
        vertices[12],
        temp1,
        vertices[5],
        temp2,
        vertices[5],
        vertices[12],
    };

    planing.push_back(std::make_unique<ColoredPolygon> (plane4, QColor(255, 255, 102)));
    planing.push_back(std::make_unique<ColoredPolygon> (plane5, QColor(255, 255, 102)));

    planing.push_back(std::make_unique<ColoredPolygon> (plane6, QColor(153, 255, 102)));
    planing.push_back(std::make_unique<ColoredPolygon> (plane7, QColor(153, 255, 102)));

    planing.push_back(std::make_unique<ColoredPolygon> (plane8, QColor(153, 204, 255)));
    planing.push_back(std::make_unique<ColoredPolygon> (plane9, QColor(153, 204, 255)));

    planing.push_back(std::make_unique<ColoredPolygon> (plane10, QColor(255, 255, 102)));
    planing.push_back(std::make_unique<ColoredPolygon> (plane11, QColor(255, 255, 102)));

    planing.push_back(std::make_unique<ColoredPolygon> (plane12, QColor(153, 255, 102)));
    planing.push_back(std::make_unique<ColoredPolygon> (plane13, QColor(153, 255, 102)));

    planing.push_back(std::make_unique<ColoredPolygon> (plane14, QColor(153, 204, 255)));
    planing.push_back(std::make_unique<ColoredPolygon> (plane15, QColor(153, 204, 255)));
}

void Decision::Remove()
{
    for (auto & edge : edges) {
        edge->Remove(); }
	
    for (auto & i : shading) {
        i->Remove(); }

    for (auto & i : planing) {
        i->Remove(); }
}
