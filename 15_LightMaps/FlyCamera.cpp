#include "FlyCamera.h"
#include <gtc/matrix_transform.hpp>


FlyCamera::FlyCamera(glm::vec3 word_up, glm::vec3 position, glm::vec3 view_direction) noexcept
	: _word_up(glm::normalize(word_up)), _position(position), _view_direction(glm::normalize(view_direction))
{}


void FlyCamera::move(glm::vec3 direction) noexcept
{
	glm::vec3 up = this->getCameraUp();
	glm::vec3 real_movement =
		direction.x * glm::cross(_view_direction, up) +
		direction.y * up +
		direction.z * _view_direction;
	_position += real_movement;
}

void FlyCamera::look(glm::vec2 direction) noexcept
{
	glm::vec3 up = this->getCameraUp();
	glm::vec3 right = glm::cross(_view_direction, up);
	glm::mat4 rotX = glm::rotate(
		glm::mat4(1.0),
		glm::radians(direction.x),
		-_word_up
	);
	glm::mat4 rotY = glm::rotate(
		glm::mat4(1.0f),
		glm::radians(direction.y),
		-right
	);
	if ((rotY * glm::vec4(up, 1.0f)).y < 0) {
		rotY = glm::mat4(1.0f);
	}
	glm::vec4 new_direction = rotY * rotX * glm::vec4(_view_direction, 1.0);
	_view_direction = glm::normalize(glm::vec3(new_direction.x, new_direction.y, new_direction.z));
	return;
}

void FlyCamera::rotate(float degree) noexcept
{
	// ignore
}

glm::mat4 FlyCamera::createTransformMatrix() const noexcept
{
	glm::vec3 up = this->getCameraUp();
	return glm::lookAt(_position, _position + _view_direction, up);
}

inline glm::vec3 FlyCamera::getPos() const noexcept
{
	return _position;
}

inline glm::vec3 FlyCamera::getViewDirection() const noexcept
{
	return _view_direction;
}


glm::vec3 FlyCamera::getCameraUp() const noexcept
{
	glm::vec3 right = glm::cross(_view_direction, _word_up);
	glm::vec3 camera_up = -glm::cross(_view_direction, right);
	if (camera_up.y <0)
		camera_up = -camera_up;
	return glm::normalize(camera_up);
}

