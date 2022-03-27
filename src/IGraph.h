#ifndef SRC_IGRAPH_H
#define SRC_IGRAPH_H

#include "IGeometric.h"

class IGraph
{
public:
	virtual void AddItem(std::shared_ptr<IGeometric> item) = 0;
	virtual void RemoveItem(std::shared_ptr<IGeometric> item) = 0;
	
	virtual ~IGraph() {};
};

#endif //SRC_IGRAPH_H
