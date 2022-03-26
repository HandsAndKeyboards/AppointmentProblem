#ifndef SRC_POLYGON_H
#define SRC_POLYGON_H

#include "IDrawable.h"
#include "IGeometric.h"

class Polygon final : public IDrawable, public IGeometric
{
	QGraphicsPolygonItem * polygon;
	
public:
	Polygon(const QVector<QPointF> & points);
	virtual ~Polygon();
	
	virtual void Translate(double dx, double dy);
	virtual void Rotate(double angle);
	virtual void Expand(double coefficient);
	virtual void Shrink(double coefficient);
	virtual QGraphicsItem * Draw(QGraphicsScene * scene);
};

#endif //SRC_POLYGON_H
