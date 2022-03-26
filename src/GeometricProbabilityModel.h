#ifndef SRC_GEOMETRICPROBABILITYMODEL_H
#define SRC_GEOMETRICPROBABILITYMODEL_H

#include <memory>

#include <QTime>

#include "IGraph.h"

class GeometricProbabilityModel final
{
	std::shared_ptr<IGraph> graph;
	
public:
	GeometricProbabilityModel();
	~GeometricProbabilityModel();
	
	double CalculateProbability(QTime timeDelta, QTime waitingInterval);
	QTime CalculateWaitingTime(QTime timeDelta, double probability);
	void UpdateGraph(QTime timeDelta, QTime waitingInterval);
};

#endif //SRC_GEOMETRICPROBABILITYMODEL_H
