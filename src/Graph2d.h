#ifndef SRC_GRAPH2D_H
#define SRC_GRAPH2D_H

#include "Axis.h"
#include "IGraph.h"

class Graph2d final : public IGraph, public IGeometric
{
	Axis xAxis;
	Axis yAxis;
	std::vector<std::shared_ptr<IGeometric>> items;
	
public:
	Graph2d(const Graph2d &) = delete;
	Graph2d(Graph2d &&) = delete;
	Graph2d & operator=(const Graph2d &) = delete;
	Graph2d & operator=(Graph2d &&) = delete;
	
	Graph2d();
	virtual ~Graph2d();
	
	virtual void AddItem(std::shared_ptr<IGeometric> item);
	virtual void RemoveItem(std::shared_ptr<IGeometric> item);
	
	virtual void Translate(double dx, double dy);
	virtual void Rotate(double angle);
	virtual void Expand(double coefficient);
	virtual void Shrink(double coefficient);
};

#endif //SRC_GRAPH2D_H
