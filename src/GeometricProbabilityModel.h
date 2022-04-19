#ifndef SRC_GEOMETRICPROBABILITYMODEL_H
#define SRC_GEOMETRICPROBABILITYMODEL_H

#include "IGraph.h"
#include "Scene.h"

class GeometricProbabilityModel final
{
	std::shared_ptr<Scene> scene; ///< 3д сцена
	
	std::shared_ptr<IGraph> activeGraph; ///< активный график, находящийся на активной сцене
	std::shared_ptr<IGraph> inactiveGraph; ///< неактивный график, находится на неактивной сцене
	
	std::tuple<float, float, QVector3D, QVector3D> activeCameraSettings; ///< параметры камеры активной сцены: cameraLinearSpeed, cameraLookSpeed, cameraPosition, cameraViewCenter
	std::tuple<float, float, QVector3D, QVector3D> inactiveCameraSettings; ///< параметры камеры неактивной сцены: cameraLinearSpeed, cameraLookSpeed, cameraPosition, cameraViewCenter

	/// установка параметров активной камеры
	void setActiveCameraSettings();

public:
	GeometricProbabilityModel(const GeometricProbabilityModel &) = delete;
	GeometricProbabilityModel(GeometricProbabilityModel &&) = delete;
	GeometricProbabilityModel() = delete;
	GeometricProbabilityModel & operator=(const GeometricProbabilityModel &) = delete;
	GeometricProbabilityModel & operator=(GeometricProbabilityModel &&) = delete;
	
	/**
	 * @brief конструирование модели
	 * @param timeDelta интервал встречи
	 * @param firstWaitingInterval интервал ожидания первой персоны
	 * @param secondWaitingInterval интервал ожидания второй персоны
	 * @param scene активная сцена
	 * @param inactiveScene неактивная сцена
	 */
	GeometricProbabilityModel(const QTime & timeDelta,
	                          int firstWaitingInterval,
	                          int secondWaitingInterval,
	                          std::shared_ptr<Scene> scene);
	~GeometricProbabilityModel() = default;
	
	/**
	 * @brief вычисление вероятности встречи
	 * @param timeDelta длина интервала встречи в минутах
	 * @param waitingIntervals массив интервалов ожидания каждой персоны в минутах
	 * @return вычисленная вероятность
	 */
	static double CalculateProbability(double timeDelta, const std::vector<int> & waitingIntervals) noexcept;
	
	/**
	 * @brief вычисление неизвестного времени ожидания
	 * @param probability вероятность встречи
	 * @param timeDelta интервал ожидания в минутах
	 * @param knownWaitingInterval известный интервал ожидания в минутах
	 * (не используется для вычисления времени ожидания трех)
	 * @return вычисленное время ожидания в минутах
	 */
	static int
	CalculateWaitingTime(double probability, double timeDelta, int knownWaitingInterval = -1);
	
	void UpdateGraph(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval);
	
	/// обмен местами активного и неактивного графиков
	void SwapGraphs();
};

#endif //SRC_GEOMETRICPROBABILITYMODEL_H
