#include <memory>
#include <cmath>

#include <QTime>

#include "GeometricProbabilityModel.h"
#include "Graph2d.h"
#include "common/mathematicFuncs.h"

/** *************************************************** PRIVATE ***************************************************** **/

/// настройка сцены для 2д графика
void GeometricProbabilityModel::form2dGraphScene()
{
	activeScene->SetCameraPerspectiveProjection(
			90,
			activeScene->Width() / activeScene->Height(),
			0.1f,
			1000.0f
	);
	activeSceneCameraSettings = std::make_tuple(100.0f, 0.0f, QVector3D{30, 30, 75}, QVector3D{30, 30, 0});
}

/// настройка сцены для 3д графика
void GeometricProbabilityModel::form3dGraphScene()
{
	/*
	 * todo тут сам подгони параметры
	 */
	inactiveScene->SetCameraPerspectiveProjection(
			90,
			inactiveScene->Width() / inactiveScene->Height(),
			0.1f,
			100.0f
	);
	inactiveSceneCameraSettings = std::make_tuple(100.0f, 100.0f, QVector3D{0, 0, 20}, QVector3D{0, 0, 0});
}

/// установка параметров активной камеры
void GeometricProbabilityModel::setActiveCameraSettings()
{
	activeScene->SetCameraLinearSpeed(std::get<0>(activeSceneCameraSettings));
	activeScene->SetCameraLookSpeed(std::get<1>(activeSceneCameraSettings));
	activeScene->SetCameraPosition(std::get<2>(activeSceneCameraSettings));
	activeScene->SetCameraViewCenter(std::get<3>(activeSceneCameraSettings));
}

/** *************************************************** PUBLIC ***************************************************** **/

/**
 * @brief конструирование модели
 * @param timeDelta интервал встречи
 * @param firstWaitingInterval интервал ожидания первой персоны
 * @param secondWaitingInterval интервал ожидания второй персоны
 * @param activeScene активная сцена
 * @param inactiveScene неактивная сцена
 */
GeometricProbabilityModel::GeometricProbabilityModel(
		const QTime & timeDelta,
		int firstWaitingInterval,
		int secondWaitingInterval,
		std::shared_ptr<Scene> activeScene,
		std::shared_ptr<Scene> inactiveScene
) :
		activeScene{activeScene},
		inactiveScene{inactiveScene}
{
	activeGraph = std::make_shared<Graph2d>(timeDelta, firstWaitingInterval, secondWaitingInterval);
	form2dGraphScene();
	activeGraph->Render(this->activeScene->GetScene());
	
//	inactiveGraph = std::make_shared<Graph3d>() // todo тут тоже не бахнуть формирование графика и сцены
//	form3dGraphScene();

	setActiveCameraSettings(); // устанавливаем настройки камеры, соответствующие активной сцене
}

/**
 * @brief вычисление вероятности встречи
 * @param timeDelta интервал времени встречи
 * @param firstWaitingInterval интервал ожидания первой персоны
 * @param secondWaitingInterval интервал ожидания второй персоны
 * @return вычисленная вероятность
 */
double GeometricProbabilityModel::CalculateProbability(
		const QTime & timeDelta,
		int firstWaitingInterval,
		int secondWaitingInterval
) noexcept
{
	double timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();
	double workingAreaSquare = timeDeltaMinutes * timeDeltaMinutes; // площадь квадрата рабочей зоны
	
	// прибавляем первую трапецию
	double hexagonArea = workingAreaSquare / 2 - pow(timeDeltaMinutes - firstWaitingInterval, 2) / 2;
	// прибавляем вторую трапецию
	hexagonArea += workingAreaSquare / 2 - pow(timeDeltaMinutes - secondWaitingInterval, 2) / 2;
	
	return hexagonArea / workingAreaSquare;
}

/**
 * @brief вычисление неизвестного времени ожидания в привязке с известным
 * @param timeDelta интервал времени встречи
 * @param probability вероятность встречи
 * @param fixedWaitingInterval известное время ожидания
 * @return вычисленное время ожидания
 */
int GeometricProbabilityModel::CalculateWaitingTime(
		const QTime & timeDelta,
		double probability,
		int fixedWaitingInterval
) noexcept
{
	double timeDeltaMinutes = timeDelta.hour() * 60 + timeDelta.minute();

	double workingAreaSquare = timeDeltaMinutes * timeDeltaMinutes; // площадь квадрата рабочей зоны
	double hexagonArea = workingAreaSquare * probability; // площадь шестиугольника
	/*
	 * площадь трапеции с зафиксированной боковой стороной
	 * pow() для красоты
	 */
	double fixedTrapezeArea = workingAreaSquare / 2 - pow(timeDeltaMinutes - fixedWaitingInterval, 2) / 2;
	double unfixedTrapezeArea = hexagonArea - fixedTrapezeArea; // площадь трапеции с незафиксированной боковой стороной
	// решаем получившееся квадратное уравнение
	std::pair<double, double> solution = solveQuadratic(1, -2 * timeDeltaMinutes, 2 * unfixedTrapezeArea);
	
	return round(solution.first); // нас интересует первый корень полученного решения, округляем его для удаления погрешности
}

void GeometricProbabilityModel::UpdateGraph(
		const QTime & timeDelta,
		int firstWaitingInterval,
		int secondWaitingInterval
)
{
	activeGraph->Update(timeDelta, firstWaitingInterval, secondWaitingInterval, activeScene->GetScene());
}

void GeometricProbabilityModel::SwapGraphs()
{
	std::swap(activeGraph, inactiveGraph);
	std::swap(activeScene, inactiveScene);
	std::swap(activeSceneCameraSettings, inactiveSceneCameraSettings);
	setActiveCameraSettings();
	activeScene->GetView()->setRootEntity(activeScene->GetScene());
}
