#ifndef SRC_AXIS_H
#define SRC_AXIS_H

#include "IGeometric.h"
#include "IDrawable.h"
#include "SegmentPoint.h"

class Axis final : public IGeometric, public IDrawable
{
	QGraphicsLineItem * line;
	QGraphicsLineItem * arrowFirstPart;
	QGraphicsLineItem * arrowSecondPart;
	std::vector<SegmentPoint> segmentPoint;
	
public:
	Axis(const Axis &) = delete;
	Axis(Axis &&) = delete;
	Axis() = delete;
	Axis & operator=(const Axis &) = delete;
	Axis & operator=(Axis &&) = delete;
	
	Axis(QPointF from, QPointF to);
	virtual ~Axis();
	
	virtual void Translate(double dx, double dy);
	virtual void Rotate(double angle);
	virtual void Expand(double coefficient);
	virtual void Shrink(double coefficient);
	virtual QGraphicsItem * Draw(QGraphicsScene * scene);
};

#endif //SRC_AXIS_H
