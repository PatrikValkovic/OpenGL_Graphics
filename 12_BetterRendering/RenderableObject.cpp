#include "RenderableObject.h"
#include <gtx/transform.hpp>
#include <gtx/euler_angles.hpp>

RenderableObject::RenderableObject(BaseModel& model, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: _model(model), _scale(scale), _rotate(rotate), _translate(translate)
{}

void RenderableObject::render(GLuint program, glm::mat4 parent, glm::mat4* view, glm::mat4* projection)
{
	glm::mat4 my_transform = parent * glm::translate(_translate) * glm::yawPitchRoll(
		glm::radians(_rotate.y),
		glm::radians(_rotate.x),
		glm::radians(_rotate.z)
	) * glm::scale(_scale);
	_model.render(program, &my_transform, view, projection);
}

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

