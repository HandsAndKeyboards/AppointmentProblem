#ifndef SRC_LINE_H
#define SRC_LINE_H

#include <QVector3D>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QGoochMaterial>
#include <Qt3DExtras/QCylinderMesh>

#include "IRenderable.h"

/**
 * линия представлена тонким цилиндром
 */
class Line final : public IRenderable
{
public:
	Line(const Line &) = delete;
	Line(Line &&) = delete;
	Line() = delete;
	Line & operator=(const Line &) = delete;
	Line & operator=(Line &&) = delete;
	
	/**
	 * конструктор класса
	 * @param from начальные координаты линии
	 * @param to конечные координаты линии
	 * @param depth толщина линии
	 */
	Line(const QVector3D & from, const QVector3D & to, float depth = 0.1f);
	~Line() final;
	
	/// рендер объекта на сцене
	void Render(Qt3DCore::QEntity * scene) override;
	
	/// удаление объекта со сцены
	void Remove(Qt3DCore::QEntity * scene) override;
	
private:
	QVector3D from;
	QVector3D to;
	
	Qt3DCore::QEntity * cylinder;
	Qt3DExtras::QCylinderMesh * cylinderMesh;
	Qt3DExtras::QGoochMaterial * cylinderMaterial;
	Qt3DCore::QTransform * transform;
};

#endif //SRC_LINE_H
