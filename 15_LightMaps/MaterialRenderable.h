#ifndef __MATERIAL_RENDERABLE_H__
#define __MATERIAL_RENDERABLE_H__

#include "ComposeRenderable.h"
#include "Material.h"

class MaterialRenderable : public ComposeRenderable
{
protected:
	Material _material;
public:
	MaterialRenderable(Renderable& inner, const Material& material);

	MaterialRenderable(const MaterialRenderable&) = default;
	MaterialRenderable(MaterialRenderable&&) = default;
	MaterialRenderable& operator=(const MaterialRenderable&) = default;
	MaterialRenderable& operator=(MaterialRenderable&&) = default;
	virtual ~MaterialRenderable() = default;

	virtual void render(GLuint program) override;

	inline MaterialRenderable& setMaterial(const Material& m) noexcept {
		_material = m;
		return *this;
	}
	inline const Material& getMaterial() const noexcept {
		return _material;
	}
	inline Material& getMaterial() noexcept {
		return _material;
	}
};

#endif