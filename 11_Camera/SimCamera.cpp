#include "SimCamera.h"

#include <gtc/matrix_transform.hpp>


SimCamera::SimCamera(glm::vec3 position, glm::vec3 view_direction, glm::vec3 camera_up) noexcept
	: _position(position), _view_direction(glm::normalize(view_direction)), _up(glm::normalize(camera_up))
{
}

void SimCamera::move(glm::vec3 direction) noexcept
{
	glm::vec3 real_movement =
		direction.x * glm::cross(_view_direction, _up) +
		direction.y * _up +
		direction.z * _view_direction;
	_position += real_movement;
}

void SimCamera::look(glm::vec2 direction) noexcept
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
	_view_direction = glm::normalize(glm::vec3(new_direction.x, new_direction.y, new_direction.z));
}


void SimCamera::rotate(float degree) noexcept
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


glm::mat4 SimCamera::createTransformMatrix() const noexcept
{
	return glm::lookAt(_position, _position + _view_direction, _up);
}

inline glm::vec3 SimCamera::getPos() const noexcept
{
	return _position;
}

inline glm::vec3 SimCamera::getViewDirection() const noexcept
{
	return _view_direction;
}

glm::vec3 SimCamera::getCameraUp() const noexcept
{
	return _up;
}
