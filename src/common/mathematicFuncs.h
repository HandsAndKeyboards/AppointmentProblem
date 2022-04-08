#ifndef APPOINTMENTPROBLEM_MATHEMATICTOOLS_H
#define APPOINTMENTPROBLEM_MATHEMATICTOOLS_H

#include <QtMath>
#include <QVector3D>

/**
 * поиск угла между векторами
 * @return угол в градусах
 */
inline double angleBetweenVectors(const QVector3D & a, const QVector3D & b) noexcept
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
inline bool realEquality(T first, T second)
{
	static const T EPS = 0.00000001;
	return qAbs(first - second) < 0.00000001;
}

#endif //APPOINTMENTPROBLEM_MATHEMATICTOOLS_H
