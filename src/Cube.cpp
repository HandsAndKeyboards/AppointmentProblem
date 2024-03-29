#include <QColor>
#include "Cube.h"

// Конструктор класса
Cube::Cube(int edgeLength)
{
	// формируем вершины
    vertices.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    vertices.push_back(QVector3D(0.0f, edgeLength, 0.0f));
    vertices.push_back(QVector3D(edgeLength, edgeLength, 0.0f));
    vertices.push_back(QVector3D(edgeLength, 0.0f, 0.0f));
    vertices.push_back(QVector3D(0.0f, 0.0f, edgeLength));
    vertices.push_back(QVector3D(0.0f, edgeLength, edgeLength));
    vertices.push_back(QVector3D(edgeLength, edgeLength, edgeLength));
    vertices.push_back(QVector3D(edgeLength, 0.0f, edgeLength));
	
	// формируем грани
	edges.push_back(std::make_unique<Line>(vertices[0], vertices[1], QColor()));
	edges.push_back(std::make_unique<Line>(vertices[1], vertices[2], QColor()));
	edges.push_back(std::make_unique<Line>(vertices[2], vertices[3], QColor()));
	edges.push_back(std::make_unique<Line>(vertices[3], vertices[0], QColor()));
	
	edges.push_back(std::make_unique<Line>(vertices[4], vertices[5], QColor()));
	edges.push_back(std::make_unique<Line>(vertices[5], vertices[6], QColor()));
	edges.push_back(std::make_unique<Line>(vertices[6], vertices[7], QColor()));
	edges.push_back(std::make_unique<Line>(vertices[7], vertices[4], QColor()));
	
	edges.push_back(std::make_unique<Line>(vertices[0], vertices[4], QColor()));
	edges.push_back(std::make_unique<Line>(vertices[1], vertices[5], QColor()));
	edges.push_back(std::make_unique<Line>(vertices[2], vertices[6], QColor()));
	edges.push_back(std::make_unique<Line>(vertices[3], vertices[7], QColor()));
}

// Отрисовка объекта на сцене
void Cube::Render(Qt3DCore::QEntity *scene)
{
    for (auto & edge : edges)
        edge->Render(scene);
}

// Удаление объекта со сцены
void Cube::Remove()
{
    for (auto & edge : edges)
        edge->Remove();
}
