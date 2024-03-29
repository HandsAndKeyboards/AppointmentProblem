#ifndef SRC_IRENDERABLE_H
#define SRC_IRENDERABLE_H

#include <Qt3DCore/QEntity>

struct IRenderable
{
	virtual void Render(Qt3DCore::QEntity * scene) = 0;
	virtual void Remove() = 0;
	
	virtual ~IRenderable() = default;
};

#endif //SRC_IRENDERABLE_H
