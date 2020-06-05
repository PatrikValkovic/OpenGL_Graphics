#include "ComposeObject.h"
#include <iostream>
#include "Constants.h"

ComposeObject::ComposeObject()
	: RenderableObject(nullptr)
{}

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

void ComposeObject::render(GLuint program)
{
	return RenderableObject::render(program);
}

ComposeObjectDestroy::ComposeObjectDestroy(std::vector<RenderableObject*>&& vect)
	: ComposeObject(std::move(vect))
{}

ComposeObjectDestroy::~ComposeObjectDestroy()
{
	if (VERBOSE) {
		std::cout << "Destroying ComposeObject " << this << std::endl;
	}
	for (RenderableObject* inner : _inner)
		delete inner;
}
