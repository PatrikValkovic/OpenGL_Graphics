#include "Camera.h"

#include <gtc/matrix_transform.hpp>

Camera::Camera() noexcept 
	: _position(0.0, 0.0, 0.0), _view_direction(0.0, 0.0, -1.0), _up(0.0, 1.0, 0.0)
{
}

void Camera::move(glm::vec3 direction) noexcept
{
	glm::vec3 real_movement =
		direction.x * glm::cross(_view_direction, _up) + 
		direction.y * _up +
		direction.z * _view_direction;
	_position += real_movement;
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

void Camera::rotate(float degree) noexcept
{
	glm::mat4 rot_matrix = glm::rotate(glm::mat4(1.0), glm::radians(degree), _view_direction);
	glm::vec4 current_up = glm::vec4(_up, 1.0);
	glm::vec4 after_rotation = rot_matrix * current_up;
	_up = glm::normalize(glm::vec3(after_rotation.x, after_rotation.y, after_rotation.z));
}

glm::mat4 Camera::createTransformMatrix() const noexcept
{
	return glm::translate(glm::mat4(1.0f), -_position);
}
