#ifndef __MATERIAL_RENDERABLE_H__
#define __MATERIAL_RENDERABLE_H__
#include <exception>
#include "WrapRenderable.h"
#include "Material.h"

template<typename PTRTYPE = Renderable&>
class MaterialRenderable : public WrapRenderable<PTRTYPE>
{
protected:
	Material _material;
public:
	MaterialRenderable(PTRTYPE&& inner, const Material& material);

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

using MaterialRenderableRef = MaterialRenderable<Renderable&>;
using MaterialRenderablePtr = MaterialRenderable<Renderable*>;
using MaterialRenderableUniq = MaterialRenderable<std::unique_ptr<Renderable>>;
using MaterialRenderableShare = MaterialRenderable<std::shared_ptr<Renderable>>;

template<typename PTRTYPE>
MaterialRenderable<PTRTYPE>::MaterialRenderable(PTRTYPE&& inner, const Material& material)
	: WrapRenderable<PTRTYPE>(std::move(inner)), _material(material)
{}
template<>
MaterialRenderable<Renderable&>::MaterialRenderable(Renderable& inner, const Material& material)
	: WrapRenderable<Renderable&>(inner), _material(material)
{}

template<typename PTRTYPE>
void MaterialRenderable<PTRTYPE>::render(GLuint program)
{
	throw std::exception("Rendering material is not supported");
	// TODO implement
	/*
	glm::vec3 diffuse = _material.getDiffuseColor();
	glm::vec3 specular = _material.getSpecularColor();
	float specular_self = _material.getSpecularStrengthSelf();
	float specular_light = _material.getSpecularStrengthLight();
	float shininess = _material.getShininess();

	glUseProgram(program);

	GLint diffuse_loc = glGetUniformLocation(program, "material.diffuse");
	if (diffuse_loc == -1) {
		cerr << "material.diffuse uniform variable not found" << endl;
	}
	glUniform3f(diffuse_loc, diffuse.x, diffuse.y, diffuse.z);

	GLint specular_loc = glGetUniformLocation(program, "material.specular");
	if (specular_loc == -1) {
		cerr << "material.specular uniform variable not found" << endl;
	}
	glUniform3f(specular_loc, specular.x, specular.y, specular.z);

	GLint selfspecular_loc = glGetUniformLocation(program, "material.specular_self");
	if (selfspecular_loc == -1) {
		cerr << "material.specular_self uniform variable not found" << endl;
	}
	glUniform1f(selfspecular_loc, specular_self);

	GLint lightspecular_loc = glGetUniformLocation(program, "material.specular_light");
	if (lightspecular_loc == -1) {
		cerr << "material.specular_light uniform variable not found" << endl;
	}
	glUniform1f(lightspecular_loc, specular_light);

	GLint shininess_loc = glGetUniformLocation(program, "material.shininess");
	if (shininess_loc == -1) {
		cerr << "material.shininess uniform variable not found" << endl;
	}
	glUniform1f(shininess_loc, shininess);

	_inner.render(program);
	*/
}

#endif