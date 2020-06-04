#ifndef __COMPOSE_RENDERABLE_H__
#define __COMPOSER_RENDERABLE_H__
#include <vector>
#include <memory>
#include "Renderable.h"

class ComposeRenderable : public Renderable
{
protected:
	std::vector<Renderable*> _renderables;
public:
	ComposeRenderable() = default;
	ComposeRenderable(std::vector<Renderable*>&& renderables);
	ComposeRenderable(const ComposeRenderable&) = default;
	ComposeRenderable(ComposeRenderable&&) = default;
	ComposeRenderable& operator=(const ComposeRenderable&) = default;
	ComposeRenderable& operator=(ComposeRenderable&&) = default;
	virtual ~ComposeRenderable() = default;

	ComposeRenderable& addRenderable(Renderable* renderable);

	virtual void render(GLuint program) override;
};

class ComposeRenderableDestroy : public ComposeRenderable
{
public:
	ComposeRenderableDestroy() = default;
	ComposeRenderableDestroy(std::vector<Renderable*> && renderables);
	ComposeRenderableDestroy(const ComposeRenderableDestroy&) = delete;
	ComposeRenderableDestroy(ComposeRenderableDestroy&&) = default;
	ComposeRenderableDestroy& operator=(const ComposeRenderableDestroy&) = delete;
	ComposeRenderableDestroy& operator=(ComposeRenderableDestroy&&) = default;
	virtual ~ComposeRenderableDestroy();
};

#endif