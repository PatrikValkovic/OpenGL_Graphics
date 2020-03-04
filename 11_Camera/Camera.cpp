#include "Camera.h"

#include <gtc/matrix_transform.hpp>

Camera::Camera() noexcept 
	: _position(0.0, 0.0, 0.0)
{
}

void Camera::move(glm::vec3 direction) noexcept
{
	_position += direction;
}

void Camera::moveX(float direction) noexcept
{
	this->move(glm::vec3(direction, 0.0, 0.0));
}

void Camera::moveY(float direction) noexcept
{
	this->move(glm::vec3(0.0, direction, 0.0));
}

void Camera::moveZ(float direction) noexcept
{
	this->move(glm::vec3(0.0, 0.0, direction));
}

glm::mat4 Camera::createTransformMatrix() const noexcept
{
	return glm::translate(glm::mat4(1.0f), -_position);
}
