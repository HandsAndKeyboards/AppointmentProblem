#ifndef SRC_GRAPH2D_H
#define SRC_GRAPH2D_H

#include "Axis.h"
#include "IGraph.h"

class Graph2d final : public IGraph
{
	static const int NUMBER_OF_UNITS = 60; ///< количество единиц в длине стороны рабочей области
	std::unique_ptr<Axis> xAxis; ///< ось OX
	std::unique_ptr<Axis> yAxis; ///< ось OY
 	std::vector<std::unique_ptr<IRenderable>> items; ///< прочие элементы графика
	
	/**
	* @brief формирование осей координат
	* @param timeDelta временной интервал встречи
	* @param firstWaitingInterval интервал ожидания
	*/
	void addAxes(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval);
	/// создание массива с делениями на OX
	std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion> >
	xAxisFormPoints(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval);
	/// создание массива с делениями на OY
	std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion> >
	yAxisFormPoints(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval);

public:
	Graph2d(const Graph2d &) = delete;
	Graph2d(Graph2d &&) = delete;
	Graph2d() = delete;
	Graph2d & operator=(const Graph2d &) = delete;
	Graph2d & operator=(Graph2d &&) = delete;
	
	/**
	 * @brief конструирование 2д графика
	 * @param timeDelta временной интервал встречи
	 * @param firstWaitingInterval интервал ожидания в минутах
	 */
	Graph2d(const QTime & timeDelta, int firstWaitingInterval, int secondWaitingInterval);
	~Graph2d() final = default;
	
	/// рендер графика на 3д сцене
	void Render(Qt3DCore::QEntity * scene) override;
	/// удаление графика со сцены
	void Remove() override;
	/// обновление графика
	void Update(const QTime & timeDelta,
				int firstWaitingInterval,
				int secondWaitingInterval,
	            Qt3DCore::QEntity * scene) override;
};

#endif //SRC_GRAPH2D_H
