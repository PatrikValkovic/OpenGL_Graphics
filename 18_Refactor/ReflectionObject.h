#ifndef __REFLECTION_OBJECT_H__
#define __REFLECTION_OBJECT_H__
#include <glm.hpp>
#include "WrapObject.h"

class ReflectionObject : public WrapObject
{
protected:
	glm::vec3 _reflection_vector;
public:
	ReflectionObject(
		RenderableObject* renderable,
		glm::vec3 reflection_vector,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::mat3 rotate = glm::mat3(1.0f)
	);
	ReflectionObject(const ReflectionObject&) = default;
	ReflectionObject(ReflectionObject&&) = default;
	ReflectionObject& operator=(const ReflectionObject&) = default;
	ReflectionObject& operator=(ReflectionObject&&) = default;
	virtual ~ReflectionObject() = default;

	glm::mat4 getReflectionMatrix() const noexcept;
	glm::vec4 getPlaneFormula(glm::mat4 view) const noexcept;
};

#endif