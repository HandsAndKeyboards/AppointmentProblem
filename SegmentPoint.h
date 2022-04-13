#ifndef SRC_SEGMENTPOINT_H
#define SRC_SEGMENTPOINT_H

#include <Qt3DExtras/QText2DEntity>
#include <QQuaternion>

#include "IRenderable.h"
#include "Line.h"

class SegmentPoint final: public IRenderable
{
public:
	SegmentPoint(const SegmentPoint &) = delete;
	SegmentPoint(SegmentPoint &&) = delete;
	SegmentPoint() = delete;
	SegmentPoint & operator=(const SegmentPoint &) = delete;
	SegmentPoint & operator=(SegmentPoint &&) = delete;
	
	/**
	 * @brief конструктор класса
	 * @param label метка деления
	 * @param pos позиция центра деления
	 * @param length длина деления
	 * @param rotation поворот деления вокруг своего центра
	 */
	SegmentPoint(const QString & label,
				 const QVector3D & labelPos,
				 float length,
				 const QVector3D & pos,
	             const QQuaternion & rotation);
	~SegmentPoint() final;
	
	void Render(Qt3DCore::QEntity * scene) override;
	void Remove(Qt3DCore::QEntity * scene) override;
	
private:
	std::unique_ptr<Line> line; ///< деление
	QPointer<Qt3DExtras::QText2DEntity> label; ///< метка деления
};

#endif //SRC_SEGMENTPOINT_H
