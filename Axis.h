#ifndef SRC_AXIS_H
#define SRC_AXIS_H

#include <QString>

#include "IRenderable.h"
#include "Line.h"
#include "SegmentPoint.h"
#include "AxisTip.h"

class Axis final : public IRenderable
{
public:
	Axis(const Axis &) = delete;
	Axis(Axis &&) = delete;
	Axis() = delete;
	Axis & operator=(const Axis &) = delete;
	Axis & operator=(Axis &&) = delete;
	
	/**
	 * @brief ось координат
	 * @param from начальная координата
	 * @param to конечная координата
	 * @param tipLabel метка наконечника координаты
	 * @param segmentPoints массив четверок: метка, позиция метки, позиция деления, вращение деления
	 */
	Axis(const QVector3D & from,
	     const QVector3D & to,
	     const QString & tipLabel,
	     const std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion>> & segmentPoints);
	~Axis() final = default;
	
	/**
	 * @brief переустановка делений на осях координат
	 * @param segmentPoints массив четверок: метка, позиция метки, позиция деления, вращение деления
	 */
	void ResetSegmentPoints(const std::list<std::tuple<QString, QVector3D, QVector3D, QQuaternion>> & segmentPoints);
	
	void Render(Qt3DCore::QEntity * scene) override;
	void Remove(Qt3DCore::QEntity * scene) override;
	
private:
	std::unique_ptr<Line> line; ///< ось
	std::unique_ptr<AxisTip> arrow; ///< кончик оси
	std::vector< std::unique_ptr<SegmentPoint> > segmentPoints; ///< деления
	
};

#endif //SRC_AXIS_H
