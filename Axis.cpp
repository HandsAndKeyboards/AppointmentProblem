#include "Axis.h"
#include "common/mathematicFuncs.h"

/**
 * @brief ось координат
 * @param from начальная координата
 * @param to конечная координата
 * @param tipLabel метка наконечника координаты
 * @param segmentPoints пары, содержащие метку деления и ее координаты на 3д сцене
 */
Axis::Axis(
		const QVector3D & from,
		const QVector3D & to,
		const QString & tipLabel,
		const std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion>> & segmentPoints
)
{
	line = std::make_unique<Line>(from, to, 0.3f);
	arrow = std::make_unique<AxisTip>(to, findRotation(from, to), tipLabel, Qt::black);
	
	ResetSegmentPoints(segmentPoints);
}

/**
 * @brief переустановка делений на осях координат
 * @param segmentPoints массив четверок: метка, позиция метки, позиция деления, вращение деления
 */
void Axis::ResetSegmentPoints(const std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion>> & segmentPoints)
{
	for (auto & point : this->segmentPoints) { point->Remove(nullptr); }
	this->segmentPoints.clear();
	
	for (auto point: segmentPoints)
	{
		this->segmentPoints.emplace_back(
				std::make_unique<SegmentPoint>(
						std::get<0>(point),
						std::get<1>(point),
						5,
						std::get<2>(point),
						std::get<3>(point)
				)
		);
	}
}

void Axis::Render(Qt3DCore::QEntity * scene)
{
	line->Render(scene);
	arrow->Render(scene);
	for (auto & point: segmentPoints) { point->Render(scene); }
}

void Axis::Remove(Qt3DCore::QEntity * scene)
{
	line->Remove(scene);
	arrow->Render(scene);
	for (auto & point: segmentPoints) { point->Remove(scene); }
}
