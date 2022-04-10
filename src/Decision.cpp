#include <QColor>

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
}

void Decision::Remove(Qt3DCore::QEntity *scene)
{
    vertices.clear();
    for (int i = 0; i < edges.size(); i++)
        edges[i]->Remove(scene);
}
