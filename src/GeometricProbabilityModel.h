#ifndef SRC_GEOMETRICPROBABILITYMODEL_H
#define SRC_GEOMETRICPROBABILITYMODEL_H

#include "IGraph.h"

class GeometricProbabilityModel final
{
	std::shared_ptr<IGraph> graph;
	
public:
	GeometricProbabilityModel();
	~GeometricProbabilityModel() = default;
	
	/**
	 * вычисление вероятности встречи
	 * @param timeDelta интервал времени встречи
	 * @param waitingInterval интервал ожидания
	 * @return
	 */
	static double CalculateProbability(QTime timeDelta, int waitingInterval) noexcept;
	static int CalculateWaitingTime(QTime timeDelta, double probability) noexcept;
	void UpdateGraph(QTime timeDelta, QTime waitingInterval);
};

#endif //SRC_GEOMETRICPROBABILITYMODEL_H
