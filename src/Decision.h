#ifndef DECISION_H
#define DECISION_H

#include <QVector>
#include <Qt3DRender>
#include <Qt3DExtras>

#include "Line.h"
#include "IRenderable.h"

class Decision final : public IRenderable
{
    // Вершины решения - точки трехмерного графа
    QVector<QVector3D> vertices;

    // Ребра решения
    QVector<IRenderable*> edges;

    // Линии штриховки фигуры
    QVector<Line*> shading;

public:
    /* Конструктор класса
     * Принимает параметр edgeLength - длину ребра куба
     * Затем инициализирует вершины куба
     */
    Decision(int edgeLength, int cubeEdgeLen);
    ~Decision();

    // Отрисовка объекта на сцене
    void Render(Qt3DCore::QEntity *scene) override;

    // Закрашивает фигуру в цвет color
    void Shading(int doubleEdgeLength);

    // Удаление объекта со сцены
    void Remove() override;
};

#endif // DECISION_H
