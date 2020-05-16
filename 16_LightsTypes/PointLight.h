#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "BaseLight.h"

class PointLight : public BaseLight
{
protected:
	float _distance;
public:
	PointLight(float strength = 0.1f, float distance = 100.0f, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	PointLight(const PointLight&) = default;
	PointLight(PointLight&&) = default;
	PointLight& operator=(const PointLight&) = default;
	PointLight& operator=(PointLight&&) = default;
	virtual ~PointLight() = default;

	inline float getDistance() const noexcept {
		return _distance;
	}
	inline PointLight& setDistance(float distance) noexcept {
		_distance = distance;
		return *this;
	}
	inline PointLight& updateDistance(float step) noexcept {
		return this->setDistance(this->getDistance() + step);
	}
};

#endif