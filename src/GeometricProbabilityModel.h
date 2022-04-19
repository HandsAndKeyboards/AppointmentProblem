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
	 * @param timeDelta интервал времени встречи
	 * @param firstWaitingInterval интервал ожидания первой персоны
	 * @param secondWaitingInterval интервал ожидания второй персоны
	 * @return вычисленная вероятность
	 */
	static double
	CalculateProbability(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval) noexcept;
	
	/**
	 * @brief вычисление неизвестного времени ожидания в привязке с известным
	 * @param timeDelta интервал времени встречи
	 * @param probability вероятность встречи
	 * @param fixedWaitingInterval известное время ожидания
	 * @return вычисленное время ожидания
	 */
	static int CalculateWaitingTime(const QTime & timeDelta, double probability, int fixedWaitingInterval) noexcept;
	void UpdateGraph(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval);
	
	/// обмен местами активного и неактивного графиков
	void SwapGraphs();

    // Меняет режим отображения в 3д режиме
    void ChangeModeDecision(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval, bool mode);
};

#endif //SRC_GEOMETRICPROBABILITYMODEL_H
