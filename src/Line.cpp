#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QMetalRoughMaterial >

#include "Line.h"
#include "common/mathematicFuncs.h"

/** *************************************************** PUBLIC ***************************************************** **/

/**
 * @brief конструктор класса
 * @param from начальные координаты линии
 * @param to конечные координаты линии
 * @param color цвет линии
 * @param thickness толщина линии
 */
Line::Line(const QVector3D & from, const QVector3D & to, QColor color, float thickness)
{
	static const QVector3D verticalVector{0, 1, 0};
	QVector3D lineVector = to - from;
	/*
	 * Ось поворота цилиндра.
	 * Вычисляется как векторное произведение вектора начального и конечного положений
	 */
	QVector3D rotationAxis = QVector3D::crossProduct(verticalVector, lineVector);
	QQuaternion rotation = QQuaternion::fromAxisAndAngle(
			rotationAxis,
			angleBetweenVectors(verticalVector, lineVector)
	);
	
	auto * transform = new Qt3DCore::QTransform();
	transform->setTranslation(from + lineVector / 2);
	transform->setRotation(rotation);
	
	construct(lineVector.length(), transform, thickness, color);
}

 /**
  * @brief конструктор объекта
  * @param length длина линии
  * @param transform трансформация линии
  * @param color цвет линии
  * @param thickness толщина линии
  */
Line::Line(float length, Qt3DCore::QTransform * transform, QColor color, float thickness)
{
	construct(length, transform, thickness, color);
}

Line::~Line()
{
	/*
	 * компоненты цилиндра будут удалены при удалении самого цилиндра,
	 * так как при добавлении компонента на цилиндр он становится их родителем
	 * (в том случае, если у компонентов нет родителя, в данном случае
	 * при их создании родителя нет)
	 */
	
	delete cylinder;
}

/// рендер объекта на сцене
void Line::Render(Qt3DCore::QEntity * scene)
{
	cylinder->setParent(scene);
}

/// удаление объекта со сцены
void Line::Remove()
{
	cylinder->setParent(static_cast<Qt3DCore::QNode *>(nullptr));
}

/** ************************************************** PRIVATE ***************************************************** **/

/**
 * @brief конструирование объекта
 * @details здесь предполагался вызов делегирующего конструктора, но из-за невозможности вызвать один
 * конструктор из тела другого пришлось функционал выносить в отдельный метод
 * @param length длина линии
 * @param transform трансформация линии
 * @param thickness толщина линии
 * @param color цвет линии
 */
void Line::construct(float length, Qt3DCore::QTransform * transform, float thickness, QColor color)
{
	// сам цилиндр
	auto * cylinderMesh = new Qt3DExtras::QCylinderMesh();
	cylinderMesh->setRadius(thickness);
	cylinderMesh->setLength(length);
	cylinderMesh->setRings(100);
	cylinderMesh->setSlices(20);
	
	// материал цилиндра
	auto * cylinderMaterial = new Qt3DExtras::QMetalRoughMaterial ();
	cylinderMaterial->setBaseColor(color);
	
	// формирование самой линии
	cylinder = new Qt3DCore::QEntity();
	cylinder->addComponent(cylinderMesh);
	cylinder->addComponent(cylinderMaterial);
	cylinder->addComponent(transform);
}