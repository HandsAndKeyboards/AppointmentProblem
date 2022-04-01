#ifndef SRC_SEGMENTPOINT_H
#define SRC_SEGMENTPOINT_H

#include <Qt3DExtras/QText2DEntity>

#include "IRenderable.h"
#include "Line.h"

class SegmentPoint final: public IRenderable
{
	std::shared_ptr<Line> line;
	std::shared_ptr<Qt3DExtras::QText2DEntity> label;
	
public:
	SegmentPoint(const SegmentPoint &) = delete;
	SegmentPoint(SegmentPoint &&) = delete;
	SegmentPoint() = delete;
	SegmentPoint & operator=(const SegmentPoint &) = delete;
	SegmentPoint & operator=(SegmentPoint &&) = delete;
	
	SegmentPoint(const std::string & label, const QVector3D & pos);
	~SegmentPoint() final;
	
	void Render(Qt3DCore::QNode * scene) override;
	void Remove(Qt3DCore::QNode * scene) override;
};

#endif //SRC_SEGMENTPOINT_H
