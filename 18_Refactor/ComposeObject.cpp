#include "ComposeObject.h"


ComposeObject::ComposeObject(std::vector<RenderableObject*>&& vect)
	: RenderableObject(nullptr), _inner(std::move(vect))
{}

ComposeObject& ComposeObject::addObject(RenderableObject* obj)
{
	_inner.push_back(obj);
	return *this;
}

void ComposeObject::render(GLuint program, glm::mat4 model)
{
	glm::mat4 my_transform = model * this->transformMatrix();

	for (RenderableObject* inner : _inner)
		inner->render(program, my_transform);
}