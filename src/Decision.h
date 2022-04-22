#ifndef DECISION_H
#define DECISION_H

#include <memory>

#include <QVector>
#include <Qt3DRender>
#include <Qt3DExtras>

#include "Line.h"
#include "IRenderable.h"

class Decision final : public IRenderable
{
    // Вершины решения - точки трехмерного графа
    std::vector<QVector3D> vertices;

    // Ребра решения
    std::vector<std::unique_ptr<IRenderable>> edges;

    // Линии штриховки фигуры
    std::vector<std::unique_ptr<IRenderable>> shading;

    // Плоскости
    std::vector<std::unique_ptr<IRenderable>> planing;

    /* Режим отображения
     * true - плоскости
     * false - закраска
     */
    bool mode;

public:
	/**
	 * @param edgeLength = waitingInterval
	 * @param cubeEdgeLen = timeDelta
     * @param mode - режим отображения
	 */
    Decision(int edgeLength, int cubeEdgeLen, bool mode);
    ~Decision() final = default;

    // Отрисовка объекта на сцене
    void Render(Qt3DCore::QEntity *scene) override;

    // Закрашивает фигуру
    void Shading();

    // Создает плоскасти вместо фигуры
    void Planing();

    // Удаление объекта со сцены
    void Remove() override;
};

#endif // DECISION_H
