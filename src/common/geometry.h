#ifndef APPOINTMENTPROBLEM_GEOMETRY_H
#define APPOINTMENTPROBLEM_GEOMETRY_H

#include <cmath>

#include <QVector3D>

/// перевод радиан в градусы
inline double radiansToDegrees(double rad) noexcept
{
	return rad * 180 / M_PI;
}

/**
 * поиск угла между векторами
 * @return угол в градусах
 */
inline double angleBetweenVectors(const QVector3D & a, const QVector3D & b) noexcept
{
	double ax = a.x(), ay = a.y(), az = a.z();
	double bx = b.x(), by = b.y(), bz = b.z();
	
	double angleCos = (ax * bx + ay * by + az * bz) / sqrt(ax * ax + ay * ay + az * az) / sqrt(bx * bx + by * by + bz * bz);
	return radiansToDegrees(acos(angleCos));
}

#endif //APPOINTMENTPROBLEM_GEOMETRY_H
