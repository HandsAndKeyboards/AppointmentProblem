#include <memory>

#include <QTime>

#include "GeometricProbabilityModel.h"
#include "Graph2d.h"

GeometricProbabilityModel::GeometricProbabilityModel()
{
	graph = std::make_shared<Graph2d>();
}

double GeometricProbabilityModel::CalculateProbability(QTime timeDelta, int waitingInterval) noexcept
{
	int timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
	
	// площадь "закрашенного" шестиугольника на графе
	double hexagonSquare = (2 * timeDeltaMinutes - waitingInterval) * waitingInterval;
	// площадь всего квадрата на графике
	double fullSquare = timeDeltaMinutes * timeDeltaMinutes;
	
	return hexagonSquare / fullSquare;
}

int GeometricProbabilityModel::CalculateWaitingTime(QTime timeDelta, double probability) noexcept
{
	int timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
	
	// площадь шестиугольника на графике
	double hexagonSquare = timeDeltaMinutes * timeDeltaMinutes * probability;
	
	/*
	 * далее решаем квадратное уравнение:
	 * waitingTime^2 - 2 * timeDeltaMinutes * waitingTime + hexagonSquare = 0
	 */
	double d = pow(2 * timeDeltaMinutes, 2) - 4 * hexagonSquare; // pow() для красоты
	double waitingTime = (2 * timeDeltaMinutes - sqrt(d)) / 2;
	
	return waitingTime;
}

void GeometricProbabilityModel::UpdateGraph(QTime timeDelta, QTime waitingInterval)
{

}
