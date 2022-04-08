#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QGoochMaterial>
#include <Qt3DCore/QTransform>

#include "Line.h"
#include "common/mathematicFuncs.h"

/**
 * @brief конструктор класса
 * @param from начальные координаты линии
 * @param to конечные координаты линии
 * @param thickness толщина линии
 */
Line::Line(const QVector3D & from, const QVector3D & to, QColor color, float thickness) : from{from}, to{to}
{
	// сам цилиндр
	auto * cylinderMesh = new Qt3DExtras::QCylinderMesh();
	cylinderMesh->setRadius(thickness);
	QVector3D lineVector(to.x() - from.x(), to.y() - from.y(), to.z() - from.z());
	cylinderMesh->setLength(lineVector.length());
	cylinderMesh->setRings(100);
	cylinderMesh->setSlices(20);
	
	// материал цилиндра
	auto * cylinderMaterial = new Qt3DExtras::QGoochMaterial();
	cylinderMaterial->setSpecular(color);
	cylinderMaterial->setShininess(5);
	
	// трансформация цилиндра
	auto * transform = new Qt3DCore::QTransform();
	// перемещаем линию к точке ее начала
	transform->setTranslation(from);
	/*
	 * По умолчанию цилиндр направлен вверх. Чтобы его "положить" на правый бок,
	 * нужно цилиндр повернуть на 90 градусов вокруг OZ. Таким образом, чтобы
	 * разместить цилиндр между заданными координатами, нужно разместить его
	 * под углом к вектору (0, 1, 0). Аналогичным образом осуществляется поворот
	 * других цилиндров
	 */
	
	const QVector3D verticalVector {0, 1, 0};
	/*
	 * Ось поворота цилиндра.
	 * Вычисляется как векторное произведение вектора начального и конечного положений
	 */
	QVector3D rotationAxis = QVector3D::crossProduct(verticalVector, lineVector);
	transform->setRotation(
			QQuaternion::fromAxisAndAngle(
					rotationAxis,
					angleBetweenVectors(verticalVector, lineVector)
			)
	);
	
	// формирование самой линии
	cylinder = new Qt3DCore::QEntity();
	cylinder->addComponent(cylinderMesh);
	cylinder->addComponent(cylinderMaterial);
	cylinder->addComponent(transform);
}

Line::~Line()
{
	/*
	 * компоненты цилиндра будут удалены при удалении самого цилиндра,
	 * так как при добавлении компонента на цилиндр он становится их родителем
	 * (в том случае, если у компонентов нет родителя, в данном случае
	 * при их создании родителя нет)
	 */
	
	cylinder.clear();
}

/// рендер объекта на сцене
void Line::Render(Qt3DCore::QEntity * scene)
{
	cylinder->setParent(scene);
}

/// удаление объекта со сцены
void Line::Remove(Qt3DCore::QEntity * scene)
{
	cylinder->setParent(static_cast<Qt3DCore::QNode *>(nullptr));
}
