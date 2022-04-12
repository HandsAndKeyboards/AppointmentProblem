#include <QColor>
#include <QByteArray>

#include "Decision.h"

/**
 * @param edgeLength = waitingInterval
 * @param cubeEdgeLen = timeDelta
 */
Decision::Decision(int edgeLength, int cubeEdgeLen)
{
	// добавляем вершины
	float minutes_per_unit = cubeEdgeLen / 60.0; // количество минут в единице координат
	
	vertices.push_back(QVector3D(0.0f, 0.0f, 0.0f));
	vertices.push_back(QVector3D(edgeLength / minutes_per_unit, 0.0f, 0.0f));
	vertices.push_back(QVector3D(edgeLength / minutes_per_unit, 0.0f, edgeLength / minutes_per_unit));
	vertices.push_back(QVector3D(edgeLength / minutes_per_unit, edgeLength / minutes_per_unit, 0.0f));
	vertices.push_back(QVector3D(0.0f, edgeLength / minutes_per_unit, 0.0f));
	vertices.push_back(QVector3D(0.0f, 0.0f, edgeLength / minutes_per_unit));
	vertices.push_back(QVector3D(0.0f, edgeLength / minutes_per_unit, edgeLength / minutes_per_unit));
	
	vertices.push_back(QVector3D(60, 60, 60));
	vertices.push_back(QVector3D(60 - edgeLength / minutes_per_unit, 60, 60));
	vertices.push_back(QVector3D(60 - edgeLength / minutes_per_unit, 60, 60 - edgeLength / minutes_per_unit));
	vertices.push_back(QVector3D(60, 60, 60 - edgeLength / minutes_per_unit));
	vertices.push_back(QVector3D(60, 60 - edgeLength / minutes_per_unit, 60 - edgeLength / minutes_per_unit));
	vertices.push_back(QVector3D(60, 60 - edgeLength / minutes_per_unit, 60));
	vertices.push_back(QVector3D(60 - edgeLength / minutes_per_unit, 60 - edgeLength / minutes_per_unit, 60));
	
	// добавляем грани
	edges.emplace_back(std::make_unique<Line>(vertices[0], vertices[1], QColor()));
	
	edges.emplace_back(std::make_unique<Line>(vertices[0], vertices[4], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[0], vertices[5], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[1], vertices[2], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[1], vertices[3], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[6], vertices[4], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[6], vertices[5], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[2], vertices[5], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[3], vertices[4], QColor()));
	
	edges.emplace_back(std::make_unique<Line>(vertices[7], vertices[8], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[7], vertices[10], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[7], vertices[12], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[10], vertices[9], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[10], vertices[11], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[13], vertices[8], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[13], vertices[12], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[9], vertices[8], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[11], vertices[12], QColor()));
	
	edges.emplace_back(std::make_unique<Line>(vertices[1], vertices[11], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[2], vertices[12], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[3], vertices[10], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[4], vertices[9], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[5], vertices[13], QColor()));
	edges.emplace_back(std::make_unique<Line>(vertices[6], vertices[8], QColor()));
	
	Shading(edgeLength, cubeEdgeLen);
}

void Decision::Render(Qt3DCore::QEntity *scene)
{
     for (auto & edge : edges)
         edge->Render(scene);

     for (auto & i : shading)
         i->Render(scene);
}

//void Decision::Shading(int edgeLength)
//{ // Закраска фигуры в цвет color
//    QVector3D temp = vertices[0];
//    QVector<QVector3D> tempVerticesBegin;
//    QVector<QVector3D> tempVerticesEnd;
//
//	int doubleEdgeLength = edgeLength * 2;
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setY(temp.y() + 0.5);
//    }
//    temp = vertices[5];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setY(temp.y() + 0.5);
//    }
//
//    // Нижний недокуб
//    temp = vertices[0];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setX(temp.x() + 0.5);
//    }
//    temp = vertices[5];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setX(temp.x() + 0.5);
//    }
//
//    temp = vertices[0];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setY(temp.y() + 0.5);
//    }
//    temp = vertices[1];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setY(temp.y() + 0.5);
//    }
//
//    temp = vertices[0];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setZ(temp.z() + 0.5);
//    }
//    temp = vertices[1];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setZ(temp.z() + 0.5);
//    }
//    // -------------------------------------
//    // Боковые грани многоугольника
//    temp = vertices[5];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setY(temp.y() + 0.5);
//    }
//    temp = vertices[13];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setY(temp.y() + 0.5);
//    }
//
//    temp = vertices[5];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setX(temp.x() + 0.5);
//    }
//    temp = vertices[13];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setX(temp.x() + 0.5);
//    }
//
//    temp = vertices[1];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setZ(temp.z() + 0.5);
//    }
//    temp = vertices[11];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setZ(temp.z() + 0.5);
//    }
//
//    temp = vertices[1];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setY(temp.y() + 0.5);
//    }
//    temp = vertices[11];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setY(temp.y() + 0.5);
//    }
//
//    temp = vertices[4];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setZ(temp.z() + 0.5);
//    }
//    temp = vertices[9];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setZ(temp.z() + 0.5);
//    }
//
//    temp = vertices[4];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setX(temp.x() + 0.5);
//    }
//    temp = vertices[9];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setX(temp.x() + 0.5);
//    }
//
//    // -------------------------------------
//    // Верхний недокуб
//
//    temp = vertices[7];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setY(temp.y() - 0.5);
//    }
//    temp = vertices[10];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setY(temp.y() - 0.5);
//    }
//
//    temp = vertices[7];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setX(temp.x() - 0.5);
//    }
//    temp = vertices[10];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setX(temp.x() - 0.5);
//    }
//
//    temp = vertices[7];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setY(temp.y() - 0.5);
//    }
//    temp = vertices[8];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setY(temp.y() - 0.5);
//    }
//
//    temp = vertices[7];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesBegin.push_back(temp);
//        temp.setZ(temp.z() - 0.5);
//    }
//    temp = vertices[8];
//    for (int i = 0; i < doubleEdgeLength; i++)
//    {
//        tempVerticesEnd.push_back(temp);
//        temp.setZ(temp.z() - 0.5);
//    }
//
//
//    for (int i = 0; i < tempVerticesBegin.size(); i++)
//    {
//        shading.push_back(std::make_unique<Line>(tempVerticesBegin[i], tempVerticesEnd[i], Qt::red));
//    }
//}

/* Создает массив с вершинами по принципу:
 *
 * значение - количество
 * 0 - 4
 * 1 - 4
 * 4 - 2
 * 5 - 4
 * 7 - 4
 * 8 - 2
 * 9 - 2
 * 10 - 2
 * 11 - 2
 * 13 - 2
 * Необходимо для оптимизации метода Shading
*/
void createTempVerticesArray(QVector<QVector3D> &arr, const std::vector<QVector3D> &vertices)
{
	for (int i = 0; i < 4; ++i) arr[i] = vertices[0];
	for (int i = 4; i < 8; ++i) arr[i] = vertices[1];
	for (int i = 8; i < 10; ++i) arr[i] = vertices[4];
	for (int i = 10; i < 14; ++i) arr[i] = vertices[5];
	for (int i = 14; i < 18; ++i) arr[i] = vertices[7];
	for (int i = 18; i < 20; ++i) arr[i] = vertices[8];
	for (int i = 20; i < 22; ++i) arr[i] = vertices[9];
	for (int i = 22; i < 24; ++i) arr[i] = vertices[10];
	for (int i = 24; i < 26; ++i) arr[i] = vertices[11];
	for (int i = 26; i < 28; ++i) arr[i] = vertices[13];
}

void Decision::Shading(int edgeLength, int timeDelta)
{ // Закраска фигуры в цвет color
	QVector<QVector3D> tempVertices(28);
	createTempVerticesArray(tempVertices, vertices); // Создае
	QVector<QVector3D> tempVerticesBegin;
	QVector<QVector3D> tempVerticesEnd;
	
	float coef = 60.0 / timeDelta;
	
	for (int i = 0; i < edgeLength; i++)
	{
		tempVertices[0];
		tempVerticesBegin.push_back(tempVertices[0]);
		tempVertices[0].setY(tempVertices[0].y() + coef);
		
		tempVertices[10];
		tempVerticesEnd.push_back(tempVertices[10]);
		tempVertices[10].setY(tempVertices[10].y() + coef);
		
		// Нижний недокуб
		
		tempVertices[1];
		tempVerticesBegin.push_back(tempVertices[1]);
		tempVertices[1].setX(tempVertices[1].x() + coef);
		
		tempVertices[13];
		tempVerticesEnd.push_back(tempVertices[13]);
		tempVertices[13].setX(tempVertices[13].x() + coef);
		
		tempVertices[2];
		tempVerticesBegin.push_back(tempVertices[2]);
		tempVertices[2].setY(tempVertices[2].y() + coef);
		
		tempVertices[4];
		tempVerticesEnd.push_back(tempVertices[4]);
		tempVertices[4].setY(tempVertices[4].y() + coef);
		
		tempVertices[3];
		tempVerticesBegin.push_back(tempVertices[3]);
		tempVertices[3].setZ(tempVertices[3].z() + coef);
		
		tempVertices[5];
		tempVerticesEnd.push_back(tempVertices[5]);
		tempVertices[5].setZ(tempVertices[5].z() + coef);
		
		// -------------------------------------
		// Боковые грани многоугольника
		
		tempVertices[11];
		tempVerticesBegin.push_back(tempVertices[11]);
		tempVertices[11].setY(tempVertices[11].y() + coef);
		
		tempVertices[26];
		tempVerticesEnd.push_back(tempVertices[26]);
		tempVertices[26].setY(tempVertices[26].y() + coef);
		
		tempVertices[12];
		tempVerticesBegin.push_back(tempVertices[12]);
		tempVertices[12].setX(tempVertices[12].x() + coef);
		
		tempVertices[27];
		tempVerticesEnd.push_back(tempVertices[27]);
		tempVertices[27].setX(tempVertices[27].x() + coef);
		
		tempVertices[6];
		tempVerticesBegin.push_back(tempVertices[6]);
		tempVertices[6].setZ(tempVertices[6].z() + coef);
		
		tempVertices[24];
		tempVerticesEnd.push_back(tempVertices[24]);
		tempVertices[24].setZ(tempVertices[24].z() + coef);
		
		tempVertices[7];
		tempVerticesBegin.push_back(tempVertices[7]);
		tempVertices[7].setY(tempVertices[7].y() + coef);
		
		tempVertices[25];
		tempVerticesEnd.push_back(tempVertices[25]);
		tempVertices[25].setY(tempVertices[25].y() + coef);
		
		tempVertices[8];
		tempVerticesBegin.push_back(tempVertices[8]);
		tempVertices[8].setZ(tempVertices[8].z() + coef);
		
		tempVertices[20];
		tempVerticesEnd.push_back(tempVertices[20]);
		tempVertices[20].setZ(tempVertices[20].z() + coef);
		
		tempVertices[9];
		tempVerticesBegin.push_back(tempVertices[9]);
		tempVertices[9].setX(tempVertices[9].x() + coef);
		
		tempVertices[21];
		tempVerticesEnd.push_back(tempVertices[21]);
		tempVertices[21].setX(tempVertices[21].x() + coef);
		
		
		// -------------------------------------
		// Верхний недокуб
		
		
		tempVertices[14];
		tempVerticesBegin.push_back(tempVertices[14]);
		tempVertices[14].setY(tempVertices[14].y() - coef);
		
		tempVertices[22];
		tempVerticesEnd.push_back(tempVertices[22]);
		tempVertices[22].setY(tempVertices[22].y() - coef);
		
		tempVertices[15];
		tempVerticesBegin.push_back(tempVertices[15]);
		tempVertices[15].setX(tempVertices[15].x() - coef);
		
		tempVertices[23];
		tempVerticesEnd.push_back(tempVertices[23]);
		tempVertices[23].setX(tempVertices[23].x() - coef);
		
		tempVertices[16];
		tempVerticesBegin.push_back(tempVertices[16]);
		tempVertices[16].setY(tempVertices[16].y() - coef);
		
		tempVertices[18];
		tempVerticesEnd.push_back(tempVertices[18]);
		tempVertices[18].setY(tempVertices[18].y() - coef);
		
		tempVertices[17];
		tempVerticesBegin.push_back(tempVertices[17]);
		tempVertices[17].setZ(tempVertices[17].z() - coef);
		
		tempVertices[19];
		tempVerticesEnd.push_back(tempVertices[19]);
		tempVertices[19].setZ(tempVertices[19].z() - coef);
	}
	
	for (int i = 0; i < tempVerticesBegin.size(); i++)
	{
		shading.push_back(std::make_unique<Line>(tempVerticesBegin[i], tempVerticesEnd[i], Qt::red));
	}
}

void Decision::Remove()
{
    for (auto & edge : edges)
        edge->Remove();
	
	for (auto & i : shading)
		i->Remove();
}
