#include "BaseLight.h"

BaseLight::BaseLight(float strength, glm::vec3 color)
	: Colorable(color), _lightStrength(strength)
{}
