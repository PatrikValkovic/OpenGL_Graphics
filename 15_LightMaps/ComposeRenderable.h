#ifndef __COMPOSE_RENDERABLE_H__
#define __COMPOSE_RENDERABLE_H__

#include "Renderable.h"

class ComposeRenderable : public Renderable
{
protected:
	const Renderable& _inner;
	ComposeRenderable(const Renderable& inner);
public:
	ComposeRenderable(const ComposeRenderable&) = default;
	ComposeRenderable(ComposeRenderable&&) = default;
	ComposeRenderable& operator=(const ComposeRenderable&) = default;
	ComposeRenderable& operator=(ComposeRenderable&&) = default;
	virtual ~ComposeRenderable() = default;
};

#endif