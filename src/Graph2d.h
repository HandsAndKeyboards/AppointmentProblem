#ifndef SRC_GRAPH2D_H
#define SRC_GRAPH2D_H

#include "Axis.h"
#include "IGraph.h"

class Graph2d final : public IGraph
{
	std::shared_ptr<Axis> xAxis;
	std::shared_ptr<Axis> yAxis;
	std::vector<std::shared_ptr<IRenderable>> items;
	
	void addAxes();

public:
	Graph2d(const Graph2d &) = delete;
	Graph2d(Graph2d &&) = delete;
	Graph2d() = delete;
	Graph2d & operator=(const Graph2d &) = delete;
	Graph2d & operator=(Graph2d &&) = delete;
	
	Graph2d(const QTime & timeDelta, int waitingInterval);
	~Graph2d() final;
	
	void Render(Qt3DCore::QNode * scene) override;
	void Remove(Qt3DCore::QNode * scene) override;
	void Update(const QTime & timeDelta, int waitingInterval) override;
};

#endif //SRC_GRAPH2D_H
