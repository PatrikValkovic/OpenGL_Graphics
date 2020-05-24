#include "WrapRenderable.h"

WrapRenderable::WrapRenderable(Renderable* inner)
	: _inner(inner)
{}

void WrapRenderable::render(GLuint program)
{
	_inner->render(program);
}

WrapRenderableDestroy::WrapRenderableDestroy(Renderable* inner)
	: WrapRenderable(inner)
{}

WrapRenderableDestroy::~WrapRenderableDestroy()
{
	delete _inner;
}
