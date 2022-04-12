#include <QColor>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras//QConeMesh>

#include "AxisTip.h"

/** *************************************************** PUBLIC ***************************************************** **/

/**
 * @brief конструктор объекта
 * @param pos позиция наконечника на 3д сцене
 * @param rotation поворот наконечника
 * @param label метка наконечника
 * @param color цвет наконечника
 * @param bottomRadius радиус нижнего круга наконечника
 * @param length длина наконечника
 */
AxisTip::AxisTip(
		const QVector3D & pos,
		const QQuaternion & rotation,
		const QString & label,
		QColor color,
		float bottomRadius, float length
)
{
	// конус
	auto * coneMesh = new Qt3DExtras::QConeMesh();
	coneMesh->setBottomRadius(bottomRadius);
	coneMesh->setLength(length);
	coneMesh->setRings(25);
	coneMesh->setSlices(15);
	
	// материал конуса
	auto * coneMaterial = new Qt3DExtras::QPhongMaterial();
	coneMaterial->setAmbient(color);
	coneMaterial->setShininess(5);
	
	// трансформация конуса
	auto * transform = new Qt3DCore::QTransform();
	// перемещаем линию к точке ее начала
	transform->setTranslation(pos);
	transform->setRotation(rotation);
	
	// формирование самой линии
	tip = new Qt3DCore::QEntity();
	tip->addComponent(coneMesh);
	tip->addComponent(coneMaterial);
	tip->addComponent(transform);
	
	// трансформация метки наконечника
	auto * labelTransform = new Qt3DCore::QTransform();
	/*
	 * сам не совсем понимаю, почему текст с позицией ниже конца оси координат показывается выше
	 */
	labelTransform->setTranslation(pos + QVector3D(1, 0, 0));
	
	// метка наконечника
	this->label = new Qt3DExtras::QText2DEntity();
	this->label->setWidth(5);
	this->label->setHeight(5);
	this->label->setText(label);
	this->label->setColor(Qt::black);
	this->label->setFont(QFont("Verdana", 3, QFont::ExtraLight));
	this->label->addComponent(labelTransform);
}

AxisTip::~AxisTip()
{
	tip.clear();
}

/// рендер объекта на сцене
void AxisTip::Render(Qt3DCore::QEntity * scene)
{
	tip->setParent(scene);
	label->setParent(scene);
}

/// удаление объекта со сцены
void AxisTip::Remove()
{
	tip->setParent(static_cast<Qt3DCore::QNode *>(nullptr));
	label->setParent(static_cast<Qt3DCore::QNode *>(nullptr));
}
