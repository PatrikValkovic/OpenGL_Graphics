#ifndef __WRAP_RENDERABLE_H__
#define __WRAP_RENDERABLE_H__
#include <memory>
#include "Renderable.h"

class WrapRenderable : public Renderable
{
protected:
	Renderable* _inner;
	WrapRenderable(Renderable* inner);
public:
	WrapRenderable() = delete;
	WrapRenderable(WrapRenderable&) = default;
	WrapRenderable(WrapRenderable&&) = default;
	WrapRenderable& operator=(const WrapRenderable&) = default;
	WrapRenderable& operator=(WrapRenderable&&) = default;
	virtual ~WrapRenderable() = default;

	virtual void render(GLuint program) override;
};


class WrapRenderableDestroy : public WrapRenderable
{
protected:
	WrapRenderableDestroy(Renderable* inner);
public:
	WrapRenderableDestroy() = delete;
	WrapRenderableDestroy(WrapRenderableDestroy&) = delete;
	WrapRenderableDestroy(WrapRenderableDestroy&&) = default;
	WrapRenderableDestroy& operator=(const WrapRenderableDestroy&) = delete;
	WrapRenderableDestroy& operator=(WrapRenderableDestroy&&) = default;
	virtual ~WrapRenderableDestroy();
};



#endif