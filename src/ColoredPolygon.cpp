#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QRenderStateSet>

#include "ColoredPolygon.h"

/** *************************************************** PUBLIC ***************************************************** **/

/**
 * @brief конструирует закрашенный многоугольник.
 * @details многоугольник должен быть триангулирован
 * @param vertices список вершин
 * @param color цвет
 */
ColoredPolygon::ColoredPolygon(const std::vector<QVector3D> & vertices, QColor color)
{
	unsigned int numOfVertices = vertices.size();
	auto * geometry = new Qt3DCore::QGeometry();
	
	// position vertices
	QByteArray bufferBytes;
	bufferBytes.resize(3 * numOfVertices * static_cast<int>(sizeof(QPointF)));
	float * positions = reinterpret_cast<float *>(bufferBytes.data());
	for (auto & point: vertices)
	{
		*positions++ = static_cast<float>(point.x());
		*positions++ = static_cast<float>(point.y());
        *positions++ = static_cast<float>(point.z());
	}
	
	auto * buf = new Qt3DCore::QBuffer(geometry);
	buf->setData(bufferBytes);
	
	auto * positionAttribute = new Qt3DCore::QAttribute(geometry);
	positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
	positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
	positionAttribute->setVertexSize(3);
	positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
	positionAttribute->setBuffer(buf);
	positionAttribute->setByteStride(3 * sizeof(float));
	positionAttribute->setCount(numOfVertices);
	geometry->addAttribute(positionAttribute); // We add the vertices in the geometry
	
	// connectivity between vertices
	QByteArray indexBytes;
	indexBytes.resize(numOfVertices * sizeof(uint32_t)); // start to end
	uint32_t * indices = reinterpret_cast<uint32_t *>(indexBytes.data());
	for (int i = 0; i < numOfVertices; ++i) { *indices++ = i; }
	
	auto * indexBuffer = new Qt3DCore::QBuffer(geometry);
	indexBuffer->setData(indexBytes);
	
	auto * indexAttribute = new Qt3DCore::QAttribute(geometry);
	indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedInt);
	indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
	indexAttribute->setBuffer(indexBuffer);
	indexAttribute->setCount(numOfVertices);
	geometry->addAttribute(indexAttribute); // We add the indices linking the points in the geometry
	
	// mesh
	Qt3DRender::QGeometryRenderer * poly = new Qt3DRender::QGeometryRenderer();
	poly->setGeometry(geometry);
	poly->setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
	
	// material
	auto * material = new Qt3DExtras::QPhongMaterial();
	material->setAmbient(color);
	
	// entity
	lineEntity = new Qt3DCore::QEntity();
	lineEntity->addComponent(poly);
	lineEntity->addComponent(material);
}

ColoredPolygon::~ColoredPolygon()
{
	lineEntity.clear();
}

void ColoredPolygon::Render(Qt3DCore::QEntity * scene)
{
	lineEntity->setParent(scene);
}

void ColoredPolygon::Remove()
{
	lineEntity->setParent(static_cast<Qt3DCore::QNode *>(nullptr));
}
