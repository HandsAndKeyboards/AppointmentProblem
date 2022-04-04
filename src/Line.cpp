#include <Qt3DCore/QBuffer>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QGeometry>
#include <Qt3DCore/QAttribute>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DExtras/QPhongMaterial>

#include "Line.h"

//Line::Line(const QVector3D & from, const QVector3D & to)
//{
//
//}

Line::~Line()
{

}

void Line::Render(Qt3DCore::QEntity * scene)
{
	Qt3DCore::QGeometry * geometry = new Qt3DCore::QGeometry(scene);
	
	// position vertices (from and to)
	QByteArray bufferBytes;
	bufferBytes.resize(3 * 2 * sizeof(float)); // from.x, from.y, from.to + to.x, to.y, to.z
	float *positions = reinterpret_cast<float*>(bufferBytes.data());
	*positions++ = from.x();
	*positions++ = from.y();
	*positions++ = from.z();
	*positions++ = to.x();
	*positions++ = to.y();
	*positions++ = to.z();
	
	auto *buf = new Qt3DCore::QBuffer(geometry);
	buf->setData(bufferBytes);
	
	auto *positionAttribute = new Qt3DCore::QAttribute(geometry);
	positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
	positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
	positionAttribute->setVertexSize(3);
	positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
	positionAttribute->setBuffer(buf);
	positionAttribute->setByteStride(3 * sizeof(float));
	positionAttribute->setCount(2);
	geometry->addAttribute(positionAttribute); // We add the vertices in the geometry
	
	// connectivity between vertices
	QByteArray indexBytes;
	indexBytes.resize(2 * sizeof(unsigned int)); // from to to
	unsigned int *indices = reinterpret_cast<unsigned int*>(indexBytes.data());
	*indices++ = 0;
	*indices++ = 1;
	
	auto *indexBuffer = new Qt3DCore::QBuffer(geometry);
	indexBuffer->setData(indexBytes);
	
	auto *indexAttribute = new Qt3DCore::QAttribute(geometry);
	indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedInt);
	indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
	indexAttribute->setBuffer(indexBuffer);
	indexAttribute->setCount(2);
	geometry->addAttribute(indexAttribute); // We add the indices linking the points in the geometry
	
	// mesh
	auto *line = new Qt3DRender::QGeometryRenderer(scene);
	line->setGeometry(geometry);
	line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
	auto *material = new Qt3DExtras::QPhongMaterial(scene);
	material->setAmbient(Qt::black);
	
	// entity
	auto *lineEntity = new Qt3DCore::QEntity(scene);
	lineEntity->addComponent(line);
	lineEntity->addComponent(material);
}

void Line::Remove(Qt3DCore::QEntity * scene)
{

}
