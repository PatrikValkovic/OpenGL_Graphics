#include "WrapRenderable.h"
#include <iostream>
#include "Constants.h"

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
	if (VERBOSE) {
		std::cout << "Destroying WrapRenderable " << this << std::endl;
	}
	delete _inner;
}
