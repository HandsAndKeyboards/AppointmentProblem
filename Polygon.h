#ifndef SRC_POLYGON_H
#define SRC_POLYGON_H

#include <QVector3D>
#include <Qpointer>
#include <Qt3DCore/QGeometry>
#include <Qt3DRender/QGeometryRenderer>

#include "IRenderable.h"
#include "Line.h"

/**
 * @brief многоугольник
 * @details отрисовывается только на плоскости XOY
 */
class Polygon final : public IRenderable
{
	QPointer<Qt3DCore::QEntity> lineEntity;
	std::vector<std::unique_ptr<Line>> borders;

public:
	Polygon(const Polygon &) = delete;
	Polygon(Polygon &&) = delete;
	Polygon() = delete;
	Polygon & operator=(const Polygon &) = delete;
	Polygon & operator=(Polygon &&) = delete;
	
	/**
	 * @brief
	 * @param vertices
	 * @param color
	 * @param borderThickness
	 */
	Polygon(const std::vector<QVector3D> & vertices, QColor color = Qt::white, float borderThickness = 0.3f);
	~Polygon() final;
	
	static std::vector<QVector3D> Triangulate(const std::vector<QVector3D> & polygon);
	
	void Render(Qt3DCore::QEntity * scene) override;
	void Remove(Qt3DCore::QEntity * scene) override;
};

#endif //SRC_POLYGON_H
