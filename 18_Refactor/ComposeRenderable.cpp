#include "ComposeRenderable.h"

ComposeRenderable::ComposeRenderable(std::vector<Renderable*>&& renderables)
	: _renderables(std::move(renderables))
{}

ComposeRenderable& ComposeRenderable::addRenderable(Renderable* renderable)
{
	_renderables.push_back(renderable);
	return *this;
}

void ComposeRenderable::render(GLuint program)
{
	for (Renderable* val : _renderables)
		val->render(program);
}



ComposeRenderableDestroy::ComposeRenderableDestroy(std::vector<Renderable*>&& renderables)
	: ComposeRenderable(std::move(renderables))
{}

ComposeRenderableDestroy::~ComposeRenderableDestroy()
{
	for (Renderable* val : _renderables)
		delete val;
}
