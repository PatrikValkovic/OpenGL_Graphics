#ifndef __WRAP_RENDERABLE_H__
#define __WRAP_RENDERABLE_H__
#include <memory>
#include "Renderable.h"

template<typename PTRTYPE = Renderable&>
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

	virtual void render(GLuint program) override;
};

using WrapRenderableRef = WrapRenderable<Renderable&>;
using WrapRenderablePtr = WrapRenderable<Renderable*>;
using WrapRenderableUniq = WrapRenderable<std::unique_ptr<Renderable>>;
using WrapRenderableShare = WrapRenderable<std::shared_ptr<Renderable>>;


template<typename PTRTYPE>
WrapRenderable<PTRTYPE>::WrapRenderable(PTRTYPE&& inner)
	: _inner(std::move(inner))
{}
template<>
WrapRenderable<Renderable&>::WrapRenderable(Renderable& inner)
	: _inner(inner)
{}


template<typename PTRTYPE>
inline void WrapRenderable<PTRTYPE>::render(GLuint program)
{
	_inner->render(program);
}
template<>
inline void WrapRenderable<Renderable&>::render(GLuint program)
{
	_inner.render(program);
}




#endif