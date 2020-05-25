#include "RenderableObject.h"
#include <iostream>
#include "Constants.h"

RenderableObject::RenderableObject()
	: RenderableObject(nullptr)
{}

RenderableObject::RenderableObject(Renderable* renderable, glm::vec3 translate, glm::vec3 scale, glm::mat3 rotate)
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

RenderableObjectDestroy::RenderableObjectDestroy(Renderable* renderable, glm::vec3 translate, glm::vec3 scale, glm::mat3 rotate)
	: RenderableObject(renderable, translate, scale, rotate)
{}

RenderableObjectDestroy::~RenderableObjectDestroy()
{
	if (VERBOSE) {
		std::cout << "Destroying RenderableObject " << this << std::endl;
	}
	delete _inner;
}
