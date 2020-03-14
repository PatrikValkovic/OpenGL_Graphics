#ifndef __LIGHT_OBJECT_H__
#define __LIGHT_OBJECT_H__

#include "RenderableModel.h"
#include "BaseModel.h"
#include "BaseLight.h"

class LightObject : public RenderableModel, public BaseLight
{
public:
	LightObject(
		BaseModel& model,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotate = glm::vec3(0.0f),
		glm::vec3 lightColor = glm::vec3(1.0f),
		float lightIntensity = 0.3f
	);


};

#endif