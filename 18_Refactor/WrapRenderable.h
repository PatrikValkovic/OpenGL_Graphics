#ifndef __WRAP_RENDERABLE_H__
#define __WRAP_RENDERABLE_H__

#include "Renderable.h"

template<typename PTRTYPE = std::unique_ptr<Renderable>>
class WrapRenderable : public Renderable
{
protected:
	PTRTYPE _inner;
	WrapRenderable(PTRTYPE&& inner);
public:
	WrapRenderable() = delete;
	WrapRenderable(WrapRenderable&) = default;
	WrapRenderable(WrapRenderable&&) = default;
	WrapRenderable& operator=(const WrapRenderable&) = default;
	WrapRenderable& operator=(WrapRenderable&&) = default;
	virtual ~WrapRenderable() = default;
};

template<typename PTRTYPE>
WrapRenderable<PTRTYPE>::WrapRenderable(PTRTYPE&& inner)
	: _inner(std::move(inner))
{}


#endif