#include "RenderableObject.h"

RenderableObject::RenderableObject(glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: _scale(scale), _rotate(rotate), _translate(translate)
{}

RenderableObject& RenderableObject::moveTo(glm::vec3 where) noexcept
{
	_translate = where;
	return *this;
}

RenderableObject& RenderableObject::moveBy(glm::vec3 by) noexcept
{
	_translate += by;
	return *this;
}

RenderableObject& RenderableObject::moveX(float distance) noexcept
{
	return this->moveBy(glm::vec3(distance, 0.0f, 0.0f));
}

RenderableObject& RenderableObject::moveY(float distance) noexcept
{
	return this->moveBy(glm::vec3(0.0f, distance, 0.0f));
}

RenderableObject& RenderableObject::moveZ(float distance) noexcept
{
	return this->moveBy(glm::vec3(0.0f, 0.0f, distance));
}

RenderableObject& RenderableObject::scale(glm::vec3 scale) noexcept
{
	_scale *= scale;
	return *this;
}

RenderableObject& RenderableObject::scaleX(float ratio) noexcept
{
	this->scale(glm::vec3(ratio, 1.0f, 1.0f));
	return *this;
}

RenderableObject& RenderableObject::scaleY(float ratio) noexcept
{
	this->scale(glm::vec3(1.0, ratio, 1.0f));
	return *this;
}

RenderableObject& RenderableObject::scaleZ(float ratio) noexcept
{
	this->scale(glm::vec3(1.0, ratio, 1.0f));
	return *this;
}

RenderableObject& RenderableObject::rotate(glm::vec3 rotation) noexcept
{
	return *this;
}

RenderableObject& RenderableObject::rotateAroundX(float degree) noexcept
{
	this->rotate(glm::vec3(degree, 0.0f, 0.0f));
	return *this;
}

RenderableObject& RenderableObject::rotateAroundY(float degree) noexcept
{
	this->rotate(glm::vec3(0.0f, degree, 0.0f));
	return *this;
}

RenderableObject& RenderableObject::rotateAroundZ(float degree) noexcept
{
	this->rotate(glm::vec3(0.0f, 0.0f, degree));
	return *this;
}

