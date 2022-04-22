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
 * @param timeDelta длина интервала встречи в минутах
 * @param waitingIntervals массив интервалов ожидания каждой персоны в минутах
 * @return вычисленная вероятность
 */
double GeometricProbabilityModel::CalculateProbability(
		double timeDelta,
		const std::vector<int> & waitingIntervals
) noexcept
{
	/*
	 * формула для вычисления вероятности: p = n * h^(n - 1) - (n - 1) * h^n, где:
	 * h - отношение времени ожидания к длине интервала встречи,
	 * n - количество персон
	 */
	
	double numberOfPersons = waitingIntervals.size();
	double probability = 0;
	for (int i = 0; i < numberOfPersons; ++i)
	{
		probability += (numberOfPersons * pow(waitingIntervals[i] / timeDelta, numberOfPersons - 1) -
				        (numberOfPersons - 1) * pow(waitingIntervals[i] / timeDelta, numberOfPersons));
	}
	probability /= numberOfPersons;
	
	return probability;
}

/**
 * @brief вычисление неизвестного времени ожидания
 * @param probability вероятность встречи
 * @param timeDelta интервал ожидания в минутах
 * @param knownWaitingInterval известный интервал ожидания в минутах
 * (не используется для вычисления времени ожидания трех)
 * @return вычисленное время ожидания в минутах
 */
int GeometricProbabilityModel::CalculateWaitingTime(
		double probability,
		double timeDelta,
		int knownWaitingInterval
)
{
	if (knownWaitingInterval != -1) // время ожидания для двух персон
	{
		/*
		 * при вычислении неизвестного времени h1 решается квадратное уравнение
		 * 2 * p = 2 * h1 - h1^2 + 2 * h2 - h2^2, где:
		 * p = probability
		 * h1 - отношение искомого время ожидания к интервалу встречи
		 * h2 - отношение неизвестного времени ожидания к интервалу встречи
		 *
		 * приведенное уравнение сводится к уравнению h1^2 - 2 * h1 + 2 * p - 2 * h2 + h2^2 = 0
		 */
		double h = knownWaitingInterval / timeDelta;
		std::array<double, 2> solution = solveQuadratic(1, -2, 2 * probability - 2 * h + h * h);
		// из-за особенностей работы solveQuadratic нас интересует только первый корень
		return round(solution[0] * timeDelta);
	}
	else // время ожидания для трех персон
	{
		/*
		 * при вычислении решается кубическое уравнение
		 * p = 3 * h ^ 2 - 2 * h ^ 3, где:
		 * p = probability
		 * h = отношение искомого времени ожидания к интервалу встречи
		 *
		 * уравнение сводится к 2 * h^3 - 3 * h^2 + p
		 */
		std::array<double, 3> solution = solveCubic(2, -3, 0, probability);
		// из-за особенностей работы solveCubic нас интересует только третий корень
		return round(solution[2] * timeDelta);
	}
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

void GeometricProbabilityModel::ChangeModeDecision(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval, bool mode)
{
    std::reinterpret_pointer_cast<Graph3d>(activeGraph)->ChangeModeDecision(mode);
    UpdateGraph(timeDelta, firstWaitingInterval, secondWaitingInterval);
}
