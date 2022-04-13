#ifndef DECISION_H
#define DECISION_H

#include <QVector>

#include "Line.h"
#include "IRenderable.h"

class Decision final : public IRenderable
{
    // Вершины решения - точки трехмерного графа
    QVector<QVector3D> vertices;

    // Ребра решения
    QVector<IRenderable*> edges;

public:
    /* Конструктор класса
     * Принимает параметр edgeLength - длину ребра куба
     * Затем инициализирует вершины куба
     */
    Decision(int edgeLength, int cubeEdgeLen);

    // Отрисовка объекта на сцене
    void Render(Qt3DCore::QEntity *scene) override;

    // Удаление объекта со сцены
    void Remove(Qt3DCore::QEntity *scene) override;
};

#endif // DECISION_H
