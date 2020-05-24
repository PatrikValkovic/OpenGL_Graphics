#include "RenderableObject.h"

RenderableObject::RenderableObject(Renderable* renderable, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: WrapRenderable(renderable), BaseObject(translate, scale, rotate)
{}


void RenderableObject::render(GLuint program)
{
	this->render(program, glm::mat4(1.0f));
}

void RenderableObject::render(GLuint program, glm::mat4 model)
{
	glm::mat4 my_transform = model * this->transformMatrix();

	BaseObject::transformations(program, &my_transform);

	_inner->render(program);
}