#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 color, float strength)
	: BaseLight(strength, color)
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
	return glm::vec3(0.0f, -1.0f, 0.0f); //TODO transformation
}
