#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, float strength)
	: BaseLight(strength, color), _direction(direction)
{}

unsigned int DirectionalLight::getType() const noexcept
{
	return 2;
}

int DirectionalLight::getParameters(float parameters[8]) const noexcept
{
	parameters[0] = this->getStrength();
	return 1;
}

glm::vec3 DirectionalLight::getDirection() const noexcept
{
	return _direction;
}
