#include "ReflectionObject.h"
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>

ReflectionObject::ReflectionObject(RenderableObject* renderable, glm::vec3 reflection_vector, glm::vec3 translate, glm::vec3 scale, glm::mat3 rotate)
	: WrapObject(renderable, translate, scale, rotate), _reflection_vector(reflection_vector)
{}

glm::mat4 ReflectionObject::getReflectionMatrix() const noexcept
{
	glm::mat4 base(1.0f);
	glm::vec3 pos = this->getPosition();
	glm::vec4 reflect_direction = this->transformMatrix() * glm::vec4(_reflection_vector, 0);
	glm::mat4 rot = 
		glm::rotate(reflect_direction.z, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(reflect_direction.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 modified_reflect = rot * reflect_direction;
	glm::mat4 reflection_matrix = glm::mat4(
		-1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	base = glm::translate(pos) * glm::inverse(rot) * reflection_matrix * rot * glm::translate(-pos) * base;
	return base;
}

glm::vec4 ReflectionObject::getPlaneFormula(glm::mat4 view) const noexcept
{
	glm::vec3 pos = glm::vec3(view * glm::vec4(this->getPosition(), 1.0f));
	glm::vec3 reflect_direction = glm::vec3(view * this->transformMatrix() * glm::vec4(_reflection_vector, 0));
	float d = -glm::dot(pos, reflect_direction);
	return glm::vec4(reflect_direction, d);
}


