#ifndef __BASE_OBJECT_H__
#define __BASE_OBJECT_H__
#include <glm.hpp>
#include <glad/glad.h>
#include "Transformable.h"
#include "UniformWrapper.h"

class BaseObject : public Transformable
{
protected:
	static UniformWrapper _uniform;
public:
	BaseObject(
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::mat3 rotate = glm::mat3(1.0f)
	);

	BaseObject(const BaseObject&) = default;
	BaseObject(BaseObject&&) = default;
	BaseObject& operator=(const BaseObject&) = default;
	BaseObject& operator=(BaseObject&&) = default;
	virtual ~BaseObject() = default;

	glm::mat4 transformMatrix() const noexcept;

	static void transformations(GLuint program, glm::mat4* model = nullptr, glm::mat4* view = nullptr, glm::mat4* projection = nullptr);
};

#endif