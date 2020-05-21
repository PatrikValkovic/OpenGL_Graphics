#ifndef __WRAP_RENDERABLE_H__
#define __WRAP_RENDERABLE_H__

#include "Renderable.h"

class WrapRenderable : public Renderable
{
protected:
	Renderable& _inner;
	WrapRenderable(Renderable& inner);
public:
	WrapRenderable(WrapRenderable&) = default;
	WrapRenderable(WrapRenderable&&) = default;
	WrapRenderable& operator=(const WrapRenderable&) = default;
	WrapRenderable& operator=(WrapRenderable&&) = default;
	virtual ~WrapRenderable() = default;
};

#endif