#include "PointLight.h"

PointLight::PointLight(float strength, float distance, glm::vec3 color)
	: BaseLight(strength, color), _distance(distance)
{}
