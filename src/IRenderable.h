#ifndef SRC_IRENDERABLE_H
#define SRC_IRENDERABLE_H

#include <Qt3DCore/QNode>

struct IRenderable
{
	virtual void Render(Qt3DCore::QNode * scene) = 0;
	virtual void Remove(Qt3DCore::QNode * scene) = 0;
	
	virtual ~IRenderable() = default;
};

#endif //SRC_IRENDERABLE_H
