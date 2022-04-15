#include <memory>
#include <cmath>

#include <QTime>

#include "GeometricProbabilityModel.h"
#include "Graph2d.h"
#include "Graph3d.h"
#include "common/mathematicFuncs.h"

/** *************************************************** PRIVATE ***************************************************** **/

/// установка параметров активной камеры
void GeometricProbabilityModel::setActiveCameraSettings()
{
	scene->SetCameraLinearSpeed(std::get<0>(activeCameraSettings));
	scene->SetCameraLookSpeed(std::get<1>(activeCameraSettings));
	scene->SetCameraPosition(std::get<2>(activeCameraSettings));
	scene->SetCameraViewCenter(std::get<3>(activeCameraSettings));
	scene->SetCameraUpVector({0, 1, 0});
}

/** *************************************************** PUBLIC ***************************************************** **/

/**
 * @brief конструирование модели
 * @param timeDelta интервал встречи
 * @param firstWaitingInterval интервал ожидания первой персоны
 * @param secondWaitingInterval интервал ожидания второй персоны
 * @param scene активная сцена
 * @param inactiveScene неактивная сцена
 */
GeometricProbabilityModel::GeometricProbabilityModel(
		const QTime & timeDelta,
		int firstWaitingInterval,
		int secondWaitingInterval,
		std::shared_ptr<Scene> scene
) : scene{scene}
{
	activeGraph = std::make_shared<Graph2d>(timeDelta, firstWaitingInterval, secondWaitingInterval);
	activeGraph->Render(this->scene->GetScene());
	inactiveGraph = std::make_shared<Graph3d>(timeDelta, firstWaitingInterval);

	activeCameraSettings = std::make_tuple(100.0f, 0.0f, QVector3D{30, 30, 75}, QVector3D{30, 30, 0});
	inactiveCameraSettings = std::make_tuple(100.0f, 100.0f, QVector3D{30, 30, 125}, QVector3D{30, 30, 0});

	// выполняется один раз, нет нужны выносить в метод setActiveCameraSettings
	scene->SetCameraPerspectiveProjection(
			90,
			scene->Width() / scene->Height(),
			0.1f,
			1000.0f
	);

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
	activeGraph->Update(timeDelta, firstWaitingInterval, secondWaitingInterval, scene->GetScene());
}

void GeometricProbabilityModel::SwapGraphs()
{
	std::swap(activeGraph, inactiveGraph); // заменяем активный график на неактивный
	inactiveGraph->Remove(); // удаляем уже неактивный график со сцены
	activeGraph->Render(scene->GetScene()); // рендерим активный график

	std::swap(activeCameraSettings, inactiveCameraSettings);
	setActiveCameraSettings();
	scene->GetView()->setRootEntity(scene->GetScene());
}
