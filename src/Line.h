#ifndef SRC_LINE_H
#define SRC_LINE_H

#include <QVector3D>
#include <QPointer>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

#include "IRenderable.h"

class Line final : public IRenderable
{
public:
	Line(const Line &) = delete;
	Line(Line &&) = delete;
	Line() = delete;
	Line & operator=(const Line &) = delete;
	Line & operator=(Line &&) = delete;
	
	/**
	 * @brief конструктор класса
	 * @param from начальные координаты линии
	 * @param to конечные координаты линии
	 * @param color цвет линии
	 * @param thickness толщина линии
	 */
	Line(const QVector3D & from, const QVector3D & to, QColor color, float thickness = 0.3f);
	 /**
	  * @brief конструктор класса
	  * @param pos позиция центра линии
	  * @param rotation поворот линии вокруг центра
	  * @param color цвет линии
	  * @param thickness толщина линии
	  */
	 Line(float length, Qt3DCore::QTransform * transform, QColor color, float thickness);
	~Line() final;
	
	/// рендер объекта на сцене
	void Render(Qt3DCore::QEntity * scene) override;
	
	/// удаление объекта со сцены
	void Remove(Qt3DCore::QEntity * scene) override;
	
private:
	QPointer<Qt3DCore::QEntity> cylinder; ///< основа линии на 3д сцене
	
	/**
	 * @brief конструирование объекта
	 * @details здесь предполагался вызов делегирующего конструктора, но из-за невозможности вызвать один
	 * конструктор из тела другого пришлось функционал выносить в отдельный метод
	 * @param length длина линии
	 * @param transform трансформация линии
	 * @param thickness толщина линии
	 * @param color цвет линии
	 */
	void construct(float length, Qt3DCore::QTransform * transform, float thickness, QColor color);
};

#endif //SRC_LINE_H
