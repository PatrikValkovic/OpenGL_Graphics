#ifndef __COMPOSE_RENDERABLE_H__
#define __COMPOSER_RENDERABLE_H__
#include <vector>
#include <memory>
#include "Renderable.h"

template<typename PTRTYPE = std::unique_ptr<Renderable>>
class ComposeRenderable : public Renderable
{
protected:
	std::vector<PTRTYPE<Renderable>> _renderables;
public:
	ComposeRenderable() = default;
	ComposeRenderable(std::vector<PTRTYPE>&& renderables);
	ComposeRenderable(const ComposeRenderable&) = default;
	ComposeRenderable(ComposeRenderable&&) = default;
	ComposeRenderable& operator=(const ComposeRenderable&) = default;
	ComposeRenderable& operator=(ComposeRenderable&&) = default;
	virtual ~ComposeRenderable() = default;

	ComposeRenderable& addRenderable(PTRTYPE&& renderable);
};


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


#endif