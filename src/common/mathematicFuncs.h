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

/**
 * @brief решение квадратного уравнения
 * @param a коэффициент a
 * @param b коэффициент b
 * @param c коэффициент c
 * @return найденные корни x1, x2
 */
inline std::pair<double, double> solveQuadratic(double a, double b, double c)
{
	double d = b * b - 4 * a * c; // дискриминант
	double dRoot = qSqrt(d);
	
	return {(-b - dRoot) / 2, (-b + dRoot) / 2};
}

/**
 * @brief решение кубического уравнения вида ax^3 + bx^2 + cx + d = 0
 * @param a коэффициент a
 * @param b коэффициент b
 * @param c коэффициент c
 * @param c коэффициент d
 * @return найденные корни x1, x2, x3
 */
inline std::array<double, 3> solveCubic(double a, double b, double c, double d)
{
	/*
	 * Метод решения по формуле Виета требует a = 1. Присутствует возможность ввести а != 1,
	 * в таком случае все коэффициенты будут сокращены на а
	 *
	 * https://planetcalc.ru/1122/
	 */
	b /= a; c /= a; d /= a; a /= a;
	double q = (b * b - 3 * c * c * c) / 9;
	double r = (2 * b * b * b - 9 * b * c + 27 * d) / 54;
	
	// todo нормальное исключение
	if (q * q * q - r * r < 0) { throw "переменная меньше нуля, комплексные числа мы еще не сделали!"; }
	double t = 1.0 / 3 * qAcos(r / qSqrt(q * q * q));
	
	double x1 = -2 * qSqrt(q) * qCos(t) - b / 3;
	double x2 = -2 * qSqrt(q) * qCos(t + 2.0 / 3 * M_PI) - b / 3;
	double x3 = -2 * qSqrt(q) * qCos(t - 2.0 / 3 * M_PI) - b / 3;
	
	return {x1, x2, x3};
}

/**
 * @brief округление числа до N знаков после запятой
 * @tparam T floating point type
 * @param num число
 * @param n число знаков после запятой
 * @return округленное число
 */
template <class T, class=std::enable_if_t<std::is_floating_point<T>::value> >
inline T round(T num, int n)
{
	T powOfTen = pow(10, n);
	return round(num * powOfTen) / powOfTen;
}

#endif //APPOINTMENTPROBLEM_MATHEMATICFUNCS_H
