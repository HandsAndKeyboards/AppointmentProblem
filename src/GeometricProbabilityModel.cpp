#include <memory>

#include <QTime>

#include "GeometricProbabilityModel.h"
#include "Graph2d.h"
#include "Graph3d.h"

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
	activeSceneCameraSettings = std::make_tuple(100.0f, 0.0f, QVector3D{30, 30, 75}, QVector3D{30, 30, 0});
}

/// настройка сцены для 3д графика
void GeometricProbabilityModel::form3dGraphScene()
{
<<<<<<<<< Temporary merge branch 1
    activeScene->SetCameraPerspectiveProjection(
            90,
            activeScene->Width() / activeScene->Height(),
            0.1f,
            1000.0f
    );
    activeScene->SetCameraLinearSpeed(100.0f);
    activeScene->SetCameraLookSpeed(100.0f);
    activeScene->SetCameraPosition({30, 30, 125});
    activeScene->SetCameraViewCenter({30, 30, 0});
=========
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
>>>>>>>>> Temporary merge branch 2
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

    inactiveGraph = std::make_shared<Graph3d>(timeDelta, waitingInterval);
    form3dGraphScene();
    inactiveGraph->Render(this->inactiveScene->GetScene());
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
	std::swap(activeSceneCameraSettings, inactiveSceneCameraSettings);
	activeScene->GetView()->setRootEntity(activeScene->GetScene());
	setActiveCameraSettings();
}
