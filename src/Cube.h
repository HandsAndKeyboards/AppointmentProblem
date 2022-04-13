#ifndef CUBE_H
#define CUBE_H

#include <QVector>

#include "Line.h"
#include "IRenderable.h"

class Cube final : public IRenderable
{
    // Вершины куба - точки трехмерного графа
    QVector<QVector3D> vertices;

    // Ребра куба
    QVector<IRenderable*> edges;

public:
    /* Конструктор класса
     * Принимает параметр edgeLength - длину ребра куба
     * Затем инициализирует вершины куба
     */
    Cube(int edgeLength);

    // Отрисовка объекта на сцене
    void Render(Qt3DCore::QEntity *scene) override;

    // Удаление объекта со сцены
    void Remove(Qt3DCore::QEntity *scene) override;
};

#endif // CUBE_H
