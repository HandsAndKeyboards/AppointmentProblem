#ifndef APPOINTMENTPROBLEM_IPOLYGON_H
#define APPOINTMENTPROBLEM_IPOLYGON_H

#include <vector>

#include <QVector3D>

#include "IRenderable.h"
namespace {
#include "include/earcut.h"
}

struct IPolygon : public IRenderable
{
	static std::vector<QVector3D> Triangulate(const std::vector<QVector3D> & polygon)
	{
		// Create array
        using Point = std::array<double, 3>;
		std::vector<std::vector<Point>> vecVecPolygon;
		std::vector<Point> vecPolygon;
		
        for (auto point: polygon) { vecPolygon.push_back({point.x(), point.y(), point.z()}); }
		
		vecVecPolygon.push_back(vecPolygon);
		
		std::vector<uint32_t> indices = mapbox::earcut<uint32_t>(vecVecPolygon);
		std::vector<QVector3D> resPolygon;
		
		for (unsigned int i = 0; i < indices.size(); ++i)
		{
			resPolygon.emplace_back(
					(vecPolygon[indices[i]])[0],
					(vecPolygon[indices[i]])[1],
                    (vecPolygon[indices[i]])[2]
			);
		}
		
		return resPolygon;
	}
};

#endif //APPOINTMENTPROBLEM_IPOLYGON_H
