#include "PointLight.h"

PointLight::PointLight(glm::vec3 attenuation, float strength, glm::vec3 color)
	: BaseLight(strength, color), AttenuatibleLight(attenuation)
{}

unsigned int PointLight::getType() const noexcept
{
	return 1;
}

int PointLight::getParameters(float parameters[8]) const noexcept
{
	parameters[0] = this->getStrength();
	parameters[1] = this->getConstantPart();
	parameters[2] = this->getLinearPart();
	parameters[3] = this->getQuadraticPart();
	return 4;
}
