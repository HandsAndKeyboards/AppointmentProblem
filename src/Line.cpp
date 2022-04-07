#include "Line.h"
#include "common/geometry.h"

/**
 * конструктор класса
 * @param from начальные координаты линии
 * @param to конечные координаты линии
 * @param depth толщина линии
 */
Line::Line(const QVector3D & from, const QVector3D & to, float depth) : from{from}, to{to}
{
	// сам цилиндр
	cylinderMesh = new Qt3DExtras::QCylinderMesh();
	cylinderMesh->setRadius(depth);
	QVector3D lineVector(to.x() - from.x(), to.y() - from.y(), to.z() - from.z());
	cylinderMesh->setLength(lineVector.length());
	cylinderMesh->setRings(100);
	cylinderMesh->setSlices(20);
	
	// материал цилиндра
	cylinderMaterial = new Qt3DExtras::QGoochMaterial();
	cylinderMaterial->setSpecular(Qt::black);
	cylinderMaterial->setShininess(5);
	
	// трансформация цилиндра
	transform = new Qt3DCore::QTransform();
	// перемещаем линию к точке ее начала
	transform->setTranslation(from);
	/*
	 * По умолчанию цилиндр направлен вверх. Чтобы его "положить" на правый бок,
	 * нужно цилиндр повернуть на -90 градусов вокруг OZ. Таким образом, чтобы
	 * разместить цилиндр между заданными координатами, нужно разместить его
	 * под углом к вектору (0, 1, 0).
	 */
	transform->setRotation(
			QQuaternion::fromAxisAndAngle(
					{0, 0, 1},
					-angleBetweenVectors({0, 1, 0}, lineVector)
			)
	);
}

Line::~Line()
{

}

/// рендер объекта на сцене
void Line::Render(Qt3DCore::QEntity * scene)
{
	cylinder = new Qt3DCore::QEntity(scene);

	cylinder->addComponent(cylinderMesh);
	cylinder->addComponent(cylinderMaterial);
	cylinder->addComponent(transform);
}

/// удаление объекта со сцены
void Line::Remove(Qt3DCore::QEntity * scene)
{

}
