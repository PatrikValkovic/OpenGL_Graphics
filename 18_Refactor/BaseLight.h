#ifndef __BASE_LIGHT_H__
#define __BASE_LIGHT_H__

#include <glm.hpp>
#include <algorithm>
#include "Colorable.h"

class BaseLight : public Colorable
{
protected:
	float _lightStrength;
	BaseLight(float strength = 0.1f, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
public:
	BaseLight(const BaseLight&) = default;
	BaseLight(BaseLight&&) = default;
	BaseLight& operator=(const BaseLight&) = default;
	BaseLight& operator=(BaseLight&&) = default;
	virtual ~BaseLight() = default;


	inline float getStrength() const noexcept {
		return _lightStrength;
	}
	inline void setStrength(float strength) noexcept {
		_lightStrength = std::max(0.0f, std::min(1.0f, strength));
	}
	inline void updateStrength(float amount) noexcept {
		this->setStrength(this->getStrength() + amount);
	}


	virtual unsigned int getType() const noexcept = 0;

	virtual glm::vec3 getDirection() const noexcept;

	virtual int getParameters(float parameters[8]) const noexcept;
};

#endif