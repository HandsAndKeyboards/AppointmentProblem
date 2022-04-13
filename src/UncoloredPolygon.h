#ifndef APPOINTMENTPROBLEM_UNCOLOREDPOLYGON_H
#define APPOINTMENTPROBLEM_UNCOLOREDPOLYGON_H

#include <QVector3D>
#include <Qt3DCore/QEntity>

#include "IPolygon.h"
#include "Line.h"

class UncoloredPolygon final : public IPolygon
{
	std::vector< std::unique_ptr<Line> > borders; ///< границы многоугольника
	
public:
	UncoloredPolygon(const UncoloredPolygon &) = delete;
	UncoloredPolygon(UncoloredPolygon &&) = delete;
	UncoloredPolygon() = delete;
	UncoloredPolygon & operator=(const UncoloredPolygon &) = delete;
	UncoloredPolygon & operator=(UncoloredPolygon &&) = delete;
	
	/**
	 * @brief конструирование незакрашенного многоугольника
	 * @param vertices вершины многоугольника
	 * @param bordersThickness толщина границы
	 * @param bordersColor цвет границы
	 */
	UncoloredPolygon(const std::vector<QVector3D> & vertices, float bordersThickness = 0.3f, QColor bordersColor = Qt::black);
	~UncoloredPolygon() final = default;
	
	void Render(Qt3DCore::QEntity * scene) override;
	void Remove() override;
};

#endif //APPOINTMENTPROBLEM_UNCOLOREDPOLYGON_H
