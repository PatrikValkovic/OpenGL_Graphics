#ifndef __LIGHT_OBJECT_H__
#define __LIGHT_OBJECT_H__

#include "RenderableModel.h"
#include "BaseModel.h"
#include "SpecularLight.h"

class LightObject : public RenderableModel, public SpecularLight
{
public:
	LightObject(
		BaseModel& model,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotate = glm::vec3(0.0f),
		glm::vec3 lightColor = glm::vec3(1.0f),
		float lightIntensity = 0.3f,
		float speculatIntensity = 0.0f,
		unsigned int reflectness = 0
	);


};

#endif