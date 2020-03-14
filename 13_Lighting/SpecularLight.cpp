#include "SpecularLight.h"

SpecularLight::SpecularLight(float lightStrength, glm::vec3 color, float specularStrength, unsigned int reflectness)
	: BaseLight(lightStrength, color), _specularStrength(specularStrength), _reflectness(reflectness)
{}
