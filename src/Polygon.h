#ifndef SRC_POLYGON_H
#define SRC_POLYGON_H

#include <QVector3D>

#include "IRenderable.h"

class Polygon final : public IRenderable
{
	std::vector<QVector3D> polygon;
	
public:
	Polygon(const Polygon &) = delete;
	Polygon(Polygon &&) = delete;
	Polygon() = delete;
	Polygon & operator=(const Polygon &) = delete;
	Polygon & operator=(Polygon &&) = delete;
	
	Polygon(const std::vector<QVector3D> & vertices);
	~Polygon() final;
	
	void Render(Qt3DCore::QEntity * scene) override;
	void Remove(Qt3DCore::QEntity * scene) override;
};

#endif //SRC_POLYGON_H
