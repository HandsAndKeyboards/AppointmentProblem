#ifndef APPOINTMENTPROBLEM_AXISTIP_H
#define APPOINTMENTPROBLEM_AXISTIP_H

#include <QPointer>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QText2DEntity>

#include "IRenderable.h"

class AxisTip final : public IRenderable
{
public:
	AxisTip(const AxisTip &) = delete;
	AxisTip(AxisTip &&) = delete;
	AxisTip() = delete;
	AxisTip & operator=(const AxisTip &) = delete;
	AxisTip & operator=(AxisTip &&) = delete;
	
	/**
	 * @brief конструктор объекта
	 * @param pos позиция наконечника на 3д сцене
	 * @param rotation поворот наконечника
	 * @param label метка наконечника
	 * @param color цвет наконечника
	 * @param bottomRadius радиус нижнего круга наконечника
	 * @param length длина наконечника
	 */
	AxisTip(const QVector3D & pos,
			const QQuaternion & rotation,
			const QString & label,
			QColor color = Qt::black,
	        float bottomRadius = 1.0f,
			float length = 2.5f);
	~AxisTip() final;
	
	/// рендер объекта на сцене
	void Render(Qt3DCore::QEntity * scene) override;
	
	/// удаление объекта со сцены
	void Remove() override;

private:
	QPointer<Qt3DCore::QEntity> tip; ///< наконечник на 3д сцене
	QPointer<Qt3DExtras::QText2DEntity> label; ///< метка наконечника
};

#endif //APPOINTMENTPROBLEM_AXISTIP_H
