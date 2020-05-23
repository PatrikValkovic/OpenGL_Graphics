#include "BaseLight.h"

BaseLight::BaseLight(float strength, glm::vec3 color)
	: Colorable(color), _lightStrength(strength)
{}

glm::vec3 BaseLight::getDirection() const noexcept
{
	return glm::vec3(1.0, 0.0, 0.0);
}

int BaseLight::getParameters(float parameters[8]) const noexcept
{
	return 0;
}
