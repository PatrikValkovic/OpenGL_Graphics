#include "LightObject.h"

LightObject::LightObject(
	BaseModel& model, 
	glm::vec3 translate, 
	glm::vec3 scale, 
	glm::vec3 rotate, 
	glm::vec3 lightColor,
	float lightIntensity,
	float speculatIntensity,
	unsigned int reflectness
) : RenderableModel(model, translate, scale, rotate), SpecularLight(lightIntensity, lightColor, speculatIntensity, reflectness)
{}
