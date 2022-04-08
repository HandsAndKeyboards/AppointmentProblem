#ifndef SRC_LINE_H
#define SRC_LINE_H

#include <QVector3D>
#include <QPointer>
#include <Qt3DCore/QEntity>

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
	 * @brief конструктор класса
	 * @param from начальные координаты линии
	 * @param to конечные координаты линии
	 * @param thickness толщина линии
	 */
	Line(const QVector3D & from, const QVector3D & to, QColor color, float thickness = 0.1f);
	~Line() final;
	
	/// рендер объекта на сцене
	void Render(Qt3DCore::QEntity * scene) override;
	
	/// удаление объекта со сцены
	void Remove(Qt3DCore::QEntity * scene) override;
	
private:
	QVector3D from; ///< начальная точка
	QVector3D to; ///< конечная точка
	
	QPointer<Qt3DCore::QEntity> cylinder; ///< основа линии на 3д сцене
};

#endif //SRC_LINE_H
