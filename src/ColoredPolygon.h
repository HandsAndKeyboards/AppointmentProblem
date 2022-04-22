#ifndef APPOINTMENTPROBLEM_COLOREDPOLYGON_H
#define APPOINTMENTPROBLEM_COLOREDPOLYGON_H

#include <QVector3D>
#include <Qpointer>
#include <Qt3DCore/QGeometry>
#include <Qt3DRender/QGeometryRenderer>

#include "IPolygon.h"
#include "Line.h"

/**
 * @brief многоугольник
 * @details отрисовывается только на плоскости XOY
 */
class ColoredPolygon final : public IPolygon
{
	QPointer<Qt3DCore::QEntity> lineEntity;

public:
	ColoredPolygon(const ColoredPolygon &) = delete;
	ColoredPolygon(ColoredPolygon &&) = delete;
	ColoredPolygon() = delete;
	ColoredPolygon & operator=(const ColoredPolygon &) = delete;
	ColoredPolygon & operator=(ColoredPolygon &&) = delete;
	
	/**
	 * @brief конструирует закрашенный многоугольник.
	 * @details многоугольник должен быть триангулирован
	 * @param vertices список вершин
	 * @param color цвет
	 */
	ColoredPolygon(const std::vector<QVector3D> & vertices, QColor color = Qt::cyan);
	~ColoredPolygon() final;
	
	void Render(Qt3DCore::QEntity * scene) override;
	void Remove() override;
};

#endif //APPOINTMENTPROBLEM_COLOREDPOLYGON_H
