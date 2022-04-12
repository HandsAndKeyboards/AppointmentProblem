#include <QColor>
#include <QPolygonF>
#include <Qt3DCore/QBuffer>
#include <QGeometry>
#include <QByteArray>

#include "Decision.h"

Decision::Decision(int edgeLength, int cubeEdgeLen)
{
    vertices.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    vertices.push_back(QVector3D(edgeLength, 0.0f, 0.0f));
    vertices.push_back(QVector3D(edgeLength, 0.0f, edgeLength));
    vertices.push_back(QVector3D(edgeLength, edgeLength, 0.0f));
    vertices.push_back(QVector3D(0.0f, edgeLength, 0.0f));
    vertices.push_back(QVector3D(0.0f, 0.0f, edgeLength));
    vertices.push_back(QVector3D(0.0f, edgeLength, edgeLength));

    vertices.push_back(QVector3D(cubeEdgeLen, cubeEdgeLen, cubeEdgeLen));
    vertices.push_back(QVector3D(cubeEdgeLen - edgeLength, cubeEdgeLen, cubeEdgeLen));
    vertices.push_back(QVector3D(cubeEdgeLen - edgeLength, cubeEdgeLen, cubeEdgeLen - edgeLength));
    vertices.push_back(QVector3D(cubeEdgeLen, cubeEdgeLen, cubeEdgeLen - edgeLength));
    vertices.push_back(QVector3D(cubeEdgeLen, cubeEdgeLen - edgeLength, cubeEdgeLen - edgeLength));
    vertices.push_back(QVector3D(cubeEdgeLen, cubeEdgeLen - edgeLength, cubeEdgeLen));
    vertices.push_back(QVector3D(cubeEdgeLen - edgeLength, cubeEdgeLen - edgeLength, cubeEdgeLen));

    Shading(edgeLength);
}

Decision::~Decision()
{
    for (auto line : shading)
        delete line;
    for (auto edge : edges)
        delete edge;
}

void Decision::Render(Qt3DCore::QEntity *scene)
{
     edges.push_back(new Line(vertices[0], vertices[1], QColor()));

     edges.push_back(new Line(vertices[0], vertices[4], QColor()));
     edges.push_back(new Line(vertices[0], vertices[5], QColor()));
     edges.push_back(new Line(vertices[1], vertices[2], QColor()));
     edges.push_back(new Line(vertices[1], vertices[3], QColor()));
     edges.push_back(new Line(vertices[6], vertices[4], QColor()));
     edges.push_back(new Line(vertices[6], vertices[5], QColor()));
     edges.push_back(new Line(vertices[2], vertices[5], QColor()));
     edges.push_back(new Line(vertices[3], vertices[4], QColor()));

     edges.push_back(new Line(vertices[7], vertices[8], QColor()));
     edges.push_back(new Line(vertices[7], vertices[10], QColor()));
     edges.push_back(new Line(vertices[7], vertices[12], QColor()));
     edges.push_back(new Line(vertices[10], vertices[9], QColor()));
     edges.push_back(new Line(vertices[10], vertices[11], QColor()));
     edges.push_back(new Line(vertices[13], vertices[8], QColor()));
     edges.push_back(new Line(vertices[13], vertices[12], QColor()));
     edges.push_back(new Line(vertices[9], vertices[8], QColor()));
     edges.push_back(new Line(vertices[11], vertices[12], QColor()));

     edges.push_back(new Line(vertices[1], vertices[11], QColor()));
     edges.push_back(new Line(vertices[2], vertices[12], QColor()));
     edges.push_back(new Line(vertices[3], vertices[10], QColor()));
     edges.push_back(new Line(vertices[4], vertices[9], QColor()));
     edges.push_back(new Line(vertices[5], vertices[13], QColor()));
     edges.push_back(new Line(vertices[6], vertices[8], QColor()));

     for (int i = 0; i < edges.size(); i++)
         edges[i]->Render(scene);

     for (int i = 0; i < shading.size(); i++)
         shading[i]->Render(scene);
}

void Decision::Shading(int edgeLength)
{ // Закраска фигуры в цвет color
    QVector3D temp = vertices[0];
    QVector<QVector3D> tempVerticesBegin;
    QVector<QVector3D> tempVerticesEnd;

    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setY(temp.y() + 0.5);
    }
    temp = vertices[5];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setY(temp.y() + 0.5);
    }

    // Нижний недокуб
    temp = vertices[0];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setX(temp.x() + 0.5);
    }
    temp = vertices[5];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setX(temp.x() + 0.5);
    }

    temp = vertices[0];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setY(temp.y() + 0.5);
    }
    temp = vertices[1];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setY(temp.y() + 0.5);
    }

    temp = vertices[0];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setZ(temp.z() + 0.5);
    }
    temp = vertices[1];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setZ(temp.z() + 0.5);
    }
    // -------------------------------------
    // Боковые грани многоугольника
    temp = vertices[5];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setY(temp.y() + 0.5);
    }
    temp = vertices[13];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setY(temp.y() + 0.5);
    }

    temp = vertices[5];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setX(temp.x() + 0.5);
    }
    temp = vertices[13];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setX(temp.x() + 0.5);
    }

    temp = vertices[1];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setZ(temp.z() + 0.5);
    }
    temp = vertices[11];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setZ(temp.z() + 0.5);
    }

    temp = vertices[1];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setY(temp.y() + 0.5);
    }
    temp = vertices[11];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setY(temp.y() + 0.5);
    }

    temp = vertices[4];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setZ(temp.z() + 0.5);
    }
    temp = vertices[9];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setZ(temp.z() + 0.5);
    }

    temp = vertices[4];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setX(temp.x() + 0.5);
    }
    temp = vertices[9];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setX(temp.x() + 0.5);
    }

    // -------------------------------------
    // Верхний недокуб

    temp = vertices[7];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setY(temp.y() - 0.5);
    }
    temp = vertices[10];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setY(temp.y() - 0.5);
    }

    temp = vertices[7];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setX(temp.x() - 0.5);
    }
    temp = vertices[10];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setX(temp.x() - 0.5);
    }

    temp = vertices[7];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setY(temp.y() - 0.5);
    }
    temp = vertices[8];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setY(temp.y() - 0.5);
    }

    temp = vertices[7];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesBegin.push_back(temp);
        temp.setZ(temp.z() - 0.5);
    }
    temp = vertices[8];
    for (int i = 0; i < edgeLength * 2; i++)
    {
        tempVerticesEnd.push_back(temp);
        temp.setZ(temp.z() - 0.5);
    }


    for (int i = 0; i < tempVerticesBegin.size(); i++)
    {
        shading.push_back(new Line(tempVerticesBegin[i], tempVerticesEnd[i], Qt::red));
    }
}

void Decision::Remove(Qt3DCore::QEntity *scene)
{
    vertices.clear();
    for (int i = 0; i < edges.size(); i++)
        edges[i]->Remove(scene);
}
