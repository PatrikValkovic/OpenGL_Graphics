#include "BaseCamera.h"

BaseCamera::~BaseCamera()
{
}


void BaseCamera::moveX(float direction) noexcept
{
	this->move(glm::vec3(direction, 0.0, 0.0));
}

void BaseCamera::moveY(float direction) noexcept
{
	this->move(glm::vec3(0.0, direction, 0.0));
}

void BaseCamera::moveZ(float direction) noexcept
{
	this->move(glm::vec3(0.0, 0.0, direction));
}

void BaseCamera::lookUp(float degree) noexcept
{
	this->look(glm::vec2(0, degree));
}

void BaseCamera::lookDown(float degree) noexcept
{
	this->lookUp(-degree);
}

void BaseCamera::lookLeft(float degree) noexcept
{
	this->look(glm::vec2(-degree, 0));
}

void BaseCamera::lookRight(float degree) noexcept
{
	this->lookLeft(-degree);
}

void BaseCamera::rotateLeft(float degree) noexcept
{
	this->rotate(-degree);
}

void BaseCamera::rotateRight(float degree) noexcept
{
	this->rotate(degree);
}

