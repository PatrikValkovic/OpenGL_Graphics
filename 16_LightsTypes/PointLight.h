#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "BaseLight.h"
#include "AttenuatibleLight.h"

class PointLight : public BaseLight, public AttenuatibleLight
{
public:
	PointLight(glm::vec3 attenuation, float strength = 1.0f, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	PointLight(const PointLight&) = default;
	PointLight(PointLight&&) = default;
	PointLight& operator=(const PointLight&) = default;
	PointLight& operator=(PointLight&&) = default;
	virtual ~PointLight() = default;

	virtual unsigned int getType() const noexcept;

	virtual int getParameters(float parameters[8]) const noexcept;
};

#endif