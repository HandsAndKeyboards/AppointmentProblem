#include "SegmentPoint.h"

/** *************************************************** PUBLIC ***************************************************** **/

/**
 * @brief конструктор класса
 * @param label метка деления
 * @param pos позиция центра деления
 * @param length длина деления
 * @param rotation поворот деления вокруг своего центра
 */
SegmentPoint::SegmentPoint(
        const QString & label,
        const QVector3D & labelPos,
        float length,
        const QVector3D & pos,
        const QQuaternion & rotation
)
{
	auto * transform = new Qt3DCore::QTransform();
	transform->setTranslation(pos);
	transform->setRotation(rotation);
	line = std::make_unique<Line>(length, transform);
	
	auto * labelTransform = new Qt3DCore::QTransform();
	labelTransform->setTranslation(labelPos);
	this->label = new Qt3DExtras::QText2DEntity();
	this->label->setWidth(15);
	this->label->setHeight(5);
	this->label->setText(label);
	this->label->setColor(Qt::black);
	this->label->setFont(QFont("Verdana", 3, QFont::ExtraLight));
	this->label->addComponent(labelTransform);
}

SegmentPoint::~SegmentPoint()
{
    label.clear();
}

void SegmentPoint::Render(Qt3DCore::QEntity * scene)
{
    line->Render(scene);
    label->setParent(scene);
}

void SegmentPoint::Remove()
{
	line->Remove();
	label->setParent(static_cast<Qt3DCore::QNode *>(nullptr));
}
