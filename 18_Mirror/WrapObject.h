#ifndef __WRAP_OBJECT_H__
#define __WRAP_OBJECT_H__
#include "RenderableObject.h"

class WrapObject : public RenderableObject
{
public:
	WrapObject(
		RenderableObject* renderable,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::mat3 rotate = glm::mat3(1.0f)
	);
	WrapObject();
	WrapObject(const WrapObject&) = default;
	WrapObject(WrapObject&&) = default;
	WrapObject& operator=(const WrapObject&) = default;
	WrapObject& operator=(WrapObject&&) = default;
	virtual ~WrapObject() = default;

	virtual void render(GLuint program, glm::mat4 model) override;
	virtual void render(GLuint program) override;
};

#endif