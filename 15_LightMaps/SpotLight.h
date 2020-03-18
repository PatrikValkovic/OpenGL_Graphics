#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "BaseLight.h"

class SpotLight : public BaseLight
{
protected:
	float _distance;
public:
	SpotLight(float strength = 0.1f, float distance = 100.0f, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	SpotLight(const SpotLight&) = default;
	SpotLight(SpotLight&&) = default;
	SpotLight& operator=(const SpotLight&) = default;
	SpotLight& operator=(SpotLight&&) = default;
	virtual ~SpotLight() = default;

	inline float getDistance() const noexcept {
		return _distance;
	}
	inline SpotLight& setDistance(float distance) noexcept {
		_distance = distance;
		return *this;
	}
	inline SpotLight& updateDistance(float step) noexcept {
		return this->setDistance(this->getDistance() + step);
	}
};

#endif