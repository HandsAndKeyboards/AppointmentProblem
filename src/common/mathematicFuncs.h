#ifndef APPOINTMENTPROBLEM_MATHEMATICFUNCS_H
#define APPOINTMENTPROBLEM_MATHEMATICFUNCS_H

#include <QtMath>
#include <QVector3D>
#include <QQuaternion>

/**
 * поиск угла между векторами
 * @return угол в градусах
 */
inline double angleBetweenVectors(QVector3D a, QVector3D b) noexcept
{
	double ax = a.x(), ay = a.y(), az = a.z();
	double bx = b.x(), by = b.y(), bz = b.z();
	
	double angleCos = (ax * bx + ay * by + az * bz) / qSqrt(ax * ax + ay * ay + az * az) / qSqrt(bx * bx + by * by + bz * bz);
	return qRadiansToDegrees(qAcos(angleCos));
}

/**
 * @brief сравнение вещественных чисел на равенство
 * @tparam T floating point type
 * @return 1, если равны, иначе 0
 */
template < class T, class=std::enable_if_t<std::is_floating_point<T>::value> >
inline bool realEquality(T first, T second) noexcept
{
	static const T EPS = 0.00000001;
	return qAbs(first - second) < EPS;
}

/**
 * @brief вычисление оси и угла поворота вектора относительно вертикальной оси OY
 * @param from начало вектора
 * @param to конец вектора
 * @return кватернион, описывающий ось поворота и угол
 */
inline QQuaternion findRotation(QVector3D from, QVector3D to)
{
	static const QVector3D verticalVector{0, 1, 0};
	QVector3D lineVector(to.x() - from.x(), to.y() - from.y(), to.z() - from.z());
	QVector3D rotationAxis = QVector3D::crossProduct(verticalVector, lineVector);
	
	return QQuaternion::fromAxisAndAngle(
			rotationAxis,
			angleBetweenVectors(verticalVector, lineVector)
	);
}

/**
 * @brief уменьшение длины вектора на заданную длину
 * @tparam T floating point type
 * @param vec вектор
 * @param length длина
 * @return уменьшенный вектор
 */
template < class T, class=std::enable_if_t<std::is_floating_point<T>::value> >
inline QVector3D operator-(QVector3D vec, T length) noexcept
{
	T lengthToEnd = vec.length();
	T lengthToStart = lengthToEnd - length;
	T similarityCoef = lengthToStart / lengthToEnd;

	return vec * similarityCoef;
}

#endif //APPOINTMENTPROBLEM_MATHEMATICFUNCS_H
