#include <QColor>

#include "UncoloredPolygon.h"

/** *************************************************** PUBLIC ***************************************************** **/

UncoloredPolygon::UncoloredPolygon(const std::vector<QVector3D> & vertices, float bordersThickness, QColor bordersColor)
{
	// связываем первые три вершины
	for (size_t i = 0, size = vertices.size() - 1; i < size; ++i)
	{
		borders.emplace_back(
				std::make_unique<Line>(
						vertices[i],
						vertices[i + 1],
						bordersColor,
						bordersThickness
				)
		);
	}
	// связываем последнюю и первую вершины
	borders.emplace_back(std::make_unique<Line>(vertices.back(), vertices.front(), bordersColor, bordersThickness));
}

void UncoloredPolygon::Render(Qt3DCore::QEntity * scene)
{
	for (auto & border: borders) { border->Render(scene); }
}

void UncoloredPolygon::Remove()
{
	for (auto & border: borders) { border->Remove(); }
}
