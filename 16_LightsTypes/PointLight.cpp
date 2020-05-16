#include "PointLight.h"

PointLight::PointLight(float strength, float distance, glm::vec3 color)
	: BaseLight(strength, color), _distance(distance)
{}

unsigned int PointLight::getType() const noexcept
{
	return 1;
}

int PointLight::getParameters(float parameters[8]) const noexcept
{
	parameters[0] = this->getDistance();
	parameters[1] = this->getStrength();
	return 2;
}
