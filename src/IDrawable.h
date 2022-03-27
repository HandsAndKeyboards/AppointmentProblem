#ifndef SRC_IDRAWABLE_H
#define SRC_IDRAWABLE_H

#include <QGraphicsScene>

class IDrawable
{
public:
	virtual QGraphicsItem * Draw(QGraphicsScene * scene) = 0;
	
	virtual ~IDrawable() {};
};

#endif //SRC_IDRAWABLE_H
