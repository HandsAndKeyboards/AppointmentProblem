#ifndef GRAPH3D_H
#define GRAPH3D_H

#include "Axis.h"
#include "IGraph.h"
#include "Cube.h"

class Graph3d final : public IGraph
{
    std::unique_ptr<Axis> xAxis; // ось OX
    std::unique_ptr<Axis> yAxis; // ось OY
    std::unique_ptr<Axis> zAxis; // ось OZ
    std::vector<std::unique_ptr<IRenderable>> items; // Прочие элементы графика

    // Создает оси на сцене
    void createAxes(const QTime & timeDelta, int waitingInterval);

    // Создает куб и внутреннюю фигуру на сцене
    void createItems(const QTime & timeDelta, int waitingInterval);

    /* Режим отображения
     * true - плоскости
     * false - закраска
     */
    bool modeDecision;

public:
    Graph3d() = delete;
    Graph3d(const Graph3d &) = delete;
    Graph3d(Graph3d &&) = delete;
    Graph3d & operator=(const Graph3d &) = delete;
    Graph3d & operator=(Graph3d &&) = delete;

    Graph3d(const QTime & timeDelta, int waitingInterval);
    ~Graph3d() final;

    void Render(Qt3DCore::QEntity * scene) override;
    void Remove() override;
	void Update(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval, Qt3DCore::QEntity * scene) override;

    // Меняет режим отображения решения
    void ChangeModeDecision(bool mode);
};

#endif // GRAPH3D_H
