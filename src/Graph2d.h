#ifndef SRC_GRAPH2D_H
#define SRC_GRAPH2D_H

#include "Axis.h"
#include "IGraph.h"

class Graph2d final : public IGraph
{
	std::unique_ptr<Axis> xAxis; ///< ось OX
	std::unique_ptr<Axis> yAxis; ///< ось OY
 	std::vector<std::unique_ptr<IRenderable>> items; ///< прочие элементы графика
	
	void addAxes(const QTime & timeDelta, int waitingInterval);

public:
	Graph2d(const Graph2d &) = delete;
	Graph2d(Graph2d &&) = delete;
	Graph2d() = delete;
	Graph2d & operator=(const Graph2d &) = delete;
	Graph2d & operator=(Graph2d &&) = delete;
	
	Graph2d(const QTime & timeDelta, int waitingInterval);
	~Graph2d() final = default;
	
	void Render(Qt3DCore::QEntity * scene) override;
	void Remove(Qt3DCore::QEntity * scene) override;
	void Update(const QTime & timeDelta, int waitingInterval, Qt3DCore::QEntity * scene) override;
};

#endif //SRC_GRAPH2D_H
