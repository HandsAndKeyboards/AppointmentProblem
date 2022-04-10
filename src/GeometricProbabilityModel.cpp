#include <memory>

#include <QTime>

#include "GeometricProbabilityModel.h"
#include "Graph2d.h"

/* **************************************************** PUBLIC ****************************************************** */

/// настройка сцены для 2д графика
void GeometricProbabilityModel::form2dGraphScene()
{
	activeScene->SetCameraPerspectiveProjection(
			90,
			activeScene->Width() / activeScene->Height(),
			0.1f,
			1000.0f
	);
	activeScene->SetCameraLinearSpeed(100.0f); // скорость перемещения камеры
	activeScene->SetCameraLookSpeed(0.0f); // скорость поворота камеры
	activeScene->SetCameraPosition({30, 30, 75});
	activeScene->SetCameraViewCenter({30, 30, 0});
}

/// настройка сцены для 3д графика
void GeometricProbabilityModel::form3dGraphScene()
{
	/*
	 * todo тут сам подгони параметры
	 */
	activeScene->SetCameraPerspectiveProjection(
			90,
			activeScene->Width() / activeScene->Height(),
			0.1f,
			100.0f
	);
	activeScene->SetCameraLinearSpeed(100.0f);
	activeScene->SetCameraLookSpeed(100.0f);
	activeScene->SetCameraPosition({0, 0, 20});
	activeScene->SetCameraViewCenter({0, 0, 0});
}

GeometricProbabilityModel::GeometricProbabilityModel(
		const QTime & timeDelta,
		int waitingInterval,
		std::shared_ptr<Scene> activeScene,
		std::shared_ptr<Scene> inactiveScene
) :
		activeScene{activeScene},
		inactiveScene{inactiveScene}
{
	activeGraph = std::make_shared<Graph2d>(timeDelta, waitingInterval);
	form2dGraphScene();
	activeGraph->Render(this->activeScene->GetScene());
	
//	inactiveGraph = std::make_shared<Graph3d>() // todo тут тоже не бахнуть формирование графика и сцены
//	form3dGraphScene();
}

/**
 * @brief вычисление вероятности встречи
 * @param timeDelta интервал времени встречи
 * @param waitingInterval интервал ожидания
 * @return вычисленная вероятность
 */
double GeometricProbabilityModel::CalculateProbability(const QTime & timeDelta, int waitingInterval) noexcept
{
	int timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
	
	// площадь "закрашенного" шестиугольника на графе
	double hexagonSquare = (2 * timeDeltaMinutes - waitingInterval) * waitingInterval;
	// площадь всего квадрата на графике
	double fullSquare = timeDeltaMinutes * timeDeltaMinutes;
	
	return hexagonSquare / fullSquare;
}

/**
 * @brief вычисление вероятности встречи
 * @param timeDelta интервал времени встречи
 * @param probability вероятность встречи
 * @return вычисленное время ожидания
 */
int GeometricProbabilityModel::CalculateWaitingTime(const QTime & timeDelta, double probability) noexcept
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

void GeometricProbabilityModel::UpdateGraph(const QTime & timeDelta, int waitingInterval)
{
	activeGraph->Update(timeDelta, waitingInterval, activeScene->GetScene());
}

void GeometricProbabilityModel::SwapGraphs()
{
	std::swap(activeGraph, inactiveGraph);
	std::swap(activeScene, inactiveScene);
	activeScene->GetView()->setRootEntity(activeScene->GetScene());
}
