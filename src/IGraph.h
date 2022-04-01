#ifndef SRC_IGRAPH_H
#define SRC_IGRAPH_H

#include "IRenderable.h"

struct IGraph : public IRenderable
{
	virtual void Update(const QTime & timeDelta, int waitingInterval) = 0;
	
	virtual ~IGraph() = default;
};

#endif //SRC_IGRAPH_H
