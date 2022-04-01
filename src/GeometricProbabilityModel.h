#ifndef SRC_GEOMETRICPROBABILITYMODEL_H
#define SRC_GEOMETRICPROBABILITYMODEL_H

#include "IGraph.h"

class GeometricProbabilityModel final
{
	std::shared_ptr<IGraph> graph;

public:
	GeometricProbabilityModel(const GeometricProbabilityModel &) = delete;
	GeometricProbabilityModel(GeometricProbabilityModel &&) = delete;
	GeometricProbabilityModel() = delete;
	GeometricProbabilityModel & operator=(const GeometricProbabilityModel &) = delete;
	GeometricProbabilityModel & operator=(GeometricProbabilityModel &&) = delete;
	
	GeometricProbabilityModel(const QTime & timeDelta, int waitingInterval);
	~GeometricProbabilityModel() = default;
	
	/**
	 * вычисление вероятности встречи
	 * @param timeDelta интервал времени встречи
	 * @param waitingInterval интервал ожидания
	 * @return вычисленная вероятность
	 */
	static double CalculateProbability(const QTime & timeDelta, int waitingInterval) noexcept;
	
	/**
	 * вычисление вероятности встречи
	 * @param timeDelta интервал времени встречи
	 * @param probability вероятность встречи
	 * @return вычисленное время ожидания
	 */
	static int CalculateWaitingTime(const QTime & timeDelta, double probability) noexcept;
	void UpdateGraph(QTime timeDelta, QTime waitingInterval);
};

#endif //SRC_GEOMETRICPROBABILITYMODEL_H
