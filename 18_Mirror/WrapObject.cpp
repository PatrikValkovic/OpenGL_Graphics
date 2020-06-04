#include "WrapObject.h"

WrapObject::WrapObject(RenderableObject* renderable, glm::vec3 translate, glm::vec3 scale, glm::mat3 rotate)
	: RenderableObject(renderable, translate, scale, rotate)
{}

WrapObject::WrapObject() : WrapObject(nullptr)
{}

void WrapObject::render(GLuint program, glm::mat4 model)
{
	if (_inner) {
		RenderableObject* obj = static_cast<RenderableObject*>(_inner);
		glm::mat4 transform = model * this->transformMatrix();
		return obj->render(program, transform);
	}
}

void WrapObject::render(GLuint program)
{
	return RenderableObject::render(program);
}
