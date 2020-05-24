#ifndef __MATERIAL_RENDERABLE_H__
#define __MATERIAL_RENDERABLE_H__
#include <exception>
#include "WrapRenderable.h"
#include "Materiable.h"

class MaterialRenderable : public WrapRenderable, public Materiable
{
public:
	MaterialRenderable(Renderable* inner, const Material& material);
	MaterialRenderable(const MaterialRenderable&) = default;
	MaterialRenderable(MaterialRenderable&&) = default;
	MaterialRenderable& operator=(const MaterialRenderable&) = default;
	MaterialRenderable& operator=(MaterialRenderable&&) = default;
	virtual ~MaterialRenderable() = default;


	virtual void render(GLuint program) override;
};

class MaterialRenderableDestroy : public WrapRenderableDestroy, public Materiable
{
public:
	MaterialRenderableDestroy(Renderable* inner, const Material& material);
	MaterialRenderableDestroy(const MaterialRenderableDestroy&) = delete;
	MaterialRenderableDestroy(MaterialRenderableDestroy&&) = default;
	MaterialRenderableDestroy& operator=(const MaterialRenderableDestroy&) = delete;
	MaterialRenderableDestroy& operator=(MaterialRenderableDestroy&&) = default;
	virtual ~MaterialRenderableDestroy() = default;


	virtual void render(GLuint program) override;
};


#endif