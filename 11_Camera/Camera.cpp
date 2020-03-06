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

void Camera::look(glm::vec2 direction) noexcept
{
	glm::mat4 rotY = glm::rotate(
		glm::mat4(1.0),
		glm::radians(direction.y), 
		-glm::cross(_view_direction, _up)
	);
	glm::mat4 rotX = glm::rotate(
		glm::mat4(1.0),
		glm::radians(direction.x),
		-_up
	);
	glm::vec4 new_up = rotX * rotY * glm::vec4(_up, 1.0f);
	_up = glm::vec3(new_up.x, new_up.y, new_up.z);
	glm::vec4 new_direction = rotX * rotY * glm::vec4(_view_direction, 1.0f);
	_view_direction = glm::vec3(new_direction.x, new_direction.y, new_direction.z);
}

void Camera::lookUp(float degree)
{
	this->look(glm::vec2(0, degree));
}

void Camera::lookDown(float degree)
{
	this->lookUp(-degree);
}

void Camera::lookLeft(float degree)
{
	this->look(glm::vec2(-degree, 0));
}

void Camera::lookRight(float degree)
{
	this->lookLeft(-degree);
}

void Camera::rotate(float degree) noexcept
{
	float one_circle_degree = glm::mod(degree, 360.0f);
	glm::vec3 right = glm::cross(_view_direction, _up);
	if (glm::abs(one_circle_degree - 90.0f) < glm::epsilon<float>() * 100){
		_up = right;
		return;
	}
	if (glm::abs(one_circle_degree - 270.0f) < glm::epsilon<float>() * 100) {
		_up = -right;
		return;
	}
	float cotg = 1 / glm::tan(glm::radians(90 - one_circle_degree));
	_up = glm::normalize(_up + right * cotg);
	if (one_circle_degree > 90 && one_circle_degree < 270)
		_up *= -1;
}


glm::mat4 Camera::createTransformMatrix() const noexcept
{
	return glm::lookAt(_position, _position + _view_direction, _up);
}
