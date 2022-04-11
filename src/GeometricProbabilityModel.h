#ifndef SRC_GEOMETRICPROBABILITYMODEL_H
#define SRC_GEOMETRICPROBABILITYMODEL_H

#include "IGraph.h"
#include "Scene.h"

class GeometricProbabilityModel final
{
	std::shared_ptr<Scene> activeScene; ///< активная сцена, находится на экране
	std::shared_ptr<Scene> inactiveScene; ///< неактивная сцена
	
	std::shared_ptr<IGraph> activeGraph; ///< активный график, находящийся на активной сцене
	std::shared_ptr<IGraph> inactiveGraph; ///< неактивный график, находится на неактивной сцене
	
	std::tuple<float, float, QVector3D, QVector3D> activeSceneCameraSettings; ///< параметры камеры активной сцены: cameraLinearSpeed, cameraLookSpeed, cameraPosition, cameraViewCenter
	std::tuple<float, float, QVector3D, QVector3D> inactiveSceneCameraSettings; ///< параметры камеры неактивной сцены: cameraLinearSpeed, cameraLookSpeed, cameraPosition, cameraViewCenter
	
	/// настройка сцены для 2д графика
	void form2dGraphScene();
	/// настройка сцены для 3д графика
	void form3dGraphScene(); // todo подбери параметры
	/// установка параметров активной камеры
	void setActiveCameraSettings();

public:
	GeometricProbabilityModel(const GeometricProbabilityModel &) = delete;
	GeometricProbabilityModel(GeometricProbabilityModel &&) = delete;
	GeometricProbabilityModel() = delete;
	GeometricProbabilityModel & operator=(const GeometricProbabilityModel &) = delete;
	GeometricProbabilityModel & operator=(GeometricProbabilityModel &&) = delete;
	
	GeometricProbabilityModel(
			const QTime & timeDelta,
			int waitingInterval,
			std::shared_ptr<Scene> activeScene,
			std::shared_ptr<Scene> inactiveScene
	);
	~GeometricProbabilityModel() = default;
	
	/**
	 * @brief вычисление вероятности встречи
	 * @param timeDelta интервал времени встречи
	 * @param waitingInterval интервал ожидания
	 * @return вычисленная вероятность
	 */
	static double CalculateProbability(const QTime & timeDelta, int waitingInterval) noexcept;
	
	/**
	 * @brief вычисление вероятности встречи
	 * @param timeDelta интервал времени встречи
	 * @param probability вероятность встречи
	 * @return вычисленное время ожидания
	 */
	static int CalculateWaitingTime(const QTime & timeDelta, double probability) noexcept;
	void UpdateGraph(const QTime & timeDelta, int waitingInterval);
	
	/// обмен местами активного и неактивного графиков
	void SwapGraphs();
};

#endif //SRC_GEOMETRICPROBABILITYMODEL_H
