#ifndef __COMPOSE_RENDERABLE_H__
#define __COMPOSER_RENDERABLE_H__
#include <vector>
#include <memory>
#include "Renderable.h"

template<typename PTRTYPE = Renderable>
class ComposeRenderable : public Renderable
{
protected:
	std::vector<PTRTYPE> _renderables;
public:
	ComposeRenderable() = default;
	ComposeRenderable(std::vector<PTRTYPE>&& renderables);
	ComposeRenderable(const ComposeRenderable&) = default;
	ComposeRenderable(ComposeRenderable&&) = default;
	ComposeRenderable& operator=(const ComposeRenderable&) = default;
	ComposeRenderable& operator=(ComposeRenderable&&) = default;
	virtual ~ComposeRenderable() = default;

	ComposeRenderable& addRenderable(PTRTYPE&& renderable);

	virtual void render(GLuint program) override;
};

using ComposeRenderableVal = ComposeRenderable<Renderable>;
using ComposeRenderablePtr = ComposeRenderable<Renderable*>;
using ComposeRenderableUniq = ComposeRenderable<std::unique_ptr<Renderable>>;
using ComposerRenderableShare = ComposeRenderable<std::shared_ptr<Renderable>>;


template<typename PTRTYPE>
ComposeRenderable<PTRTYPE>::ComposeRenderable(std::vector<PTRTYPE>&& renderables)
	: _renderables(std::move(renderables))
{}

template<typename PTRTYPE>
ComposeRenderable<PTRTYPE>& ComposeRenderable<PTRTYPE>::addRenderable(PTRTYPE&& renderable)
{
	_renderables.push_back(std::move(renderable));
	return *this;
}

template<typename PTRTYPE>
void ComposeRenderable<PTRTYPE>::render(GLuint program)
{
	for (PTRTYPE& val : _renderables)
		val->render(program);
}
template<>
inline void ComposeRenderable<Renderable>::render(GLuint program)
{
	for (Renderable& val : _renderables)
		val.render(program);
}

#endif