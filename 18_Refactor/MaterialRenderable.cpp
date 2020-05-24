#include "MaterialRenderable.h"

MaterialRenderable::MaterialRenderable(Renderable* inner, const Material& material)
	: WrapRenderable(inner), Materiable(material)
{}

void MaterialRenderable::render(GLuint program)
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

MaterialRenderableDestroy::MaterialRenderableDestroy(Renderable* inner, const Material& material)
	: WrapRenderableDestroy(inner), Materiable(material)
{}

void MaterialRenderableDestroy::render(GLuint program)
{
	throw std::exception("Rendering material is not supported");
}
