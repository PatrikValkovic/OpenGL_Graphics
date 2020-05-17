#include "Spotlight.h"

Spotlight::Spotlight(
	float innerCutoff, 
	float outerCufoff, 
	glm::vec3 direction, 
	glm::vec3 color, 
	glm::vec3 attenuation,
	float strength)
	: DirectionalLight(direction, color, strength), 
	  AttenuatibleLight(attenuation),
	  _innerCutoff(innerCutoff), _outerCutoff(outerCufoff)
{
	assert(innerCutoff < outerCufoff);
}

unsigned int Spotlight::getType() const noexcept
{
	return 3;
}

int Spotlight::getParameters(float parameters[8]) const noexcept
{
	parameters[0] = this->getStrength();
	parameters[1] = this->getInnerCutoff();
	parameters[2] = this->getOuterCutoff();
	parameters[3] = this->getConstantPart();
	parameters[4] = this->getLinearPart();
	parameters[5] = this->getQuadraticPart();
	return 6;
}
