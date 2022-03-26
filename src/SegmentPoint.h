#ifndef SRC_SEGMENTPOINT_H
#define SRC_SEGMENTPOINT_H

#include "IGeometric.h"
#include "IDrawable.h"

class SegmentPoint : public IGeometric, public IDrawable
{
	QGraphicsLineItem * line;
	QGraphicsTextItem * label;
	
public:
	SegmentPoint(const SegmentPoint &) = delete;
	SegmentPoint(SegmentPoint &&) = delete;
	SegmentPoint() = delete;
	SegmentPoint & operator=(const SegmentPoint &) = delete;
	SegmentPoint & operator=(SegmentPoint &&) = delete;
	
	SegmentPoint(std::string label, QPointF pos, double angle);
	virtual ~SegmentPoint();
	
	virtual void Translate(double dx, double dy);
	virtual void Rotate(double angle);
	virtual void Expand(double coefficient);
	virtual void Shrink(double coefficient);
	virtual QGraphicsItem * Draw(QGraphicsScene * scene);
};

#endif //SRC_SEGMENTPOINT_H
