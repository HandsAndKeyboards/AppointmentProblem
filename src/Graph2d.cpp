#include "Graph2d.h"

void Graph2d::addAxes()
{

}

Graph2d::Graph2d(const QTime & timeDelta, int waitingInterval)
{
	l = new Line({0, 0, 0}, {30, 30, 0}); // debug
}

Graph2d::~Graph2d()
{

}

void Graph2d::Render(Qt3DCore::QEntity * scene)
{
	l->Render(scene); // debug
}

void Graph2d::Remove(Qt3DCore::QEntity * scene)
{

}

void Graph2d::Update(const QTime & timeDelta, int waitingInterval)
{

}
