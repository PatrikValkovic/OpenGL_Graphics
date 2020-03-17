#include "SpotLight.h"

SpotLight::SpotLight(float strength, float distance, glm::vec3 color)
	: BaseLight(strength, color), _distance(distance)
{}
