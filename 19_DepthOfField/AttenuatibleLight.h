#ifndef __ATTENUATIBLE_LIGHT_H__
#define __ATTENUATIBLE_LIGHT_H__
#include <glm.hpp>

class AttenuatibleLight
{
protected:
	glm::vec3 _attenuation;
public:
	AttenuatibleLight(glm::vec3 attenuation);
	AttenuatibleLight(const AttenuatibleLight&) = default;
	AttenuatibleLight(AttenuatibleLight&&) = default;
	AttenuatibleLight& operator=(const AttenuatibleLight&) = default;
	AttenuatibleLight& operator=(AttenuatibleLight&&) = default;
	virtual ~AttenuatibleLight() = default;

	inline glm::vec3 getAttenuation() const noexcept {
		return _attenuation;
	}
	inline AttenuatibleLight& setAttenuation(glm::vec3 attenuation) noexcept {
		_attenuation = attenuation;
		return *this;
	}
	inline AttenuatibleLight& updateAttenuation(glm::vec3 update) noexcept {
		return this->setAttenuation(this->getAttenuation() + update);
	}
	inline float getConstantPart() const noexcept {
		return getAttenuation().x;
	}
	inline float getLinearPart() const noexcept {
		return getAttenuation().y;
	}
	inline float getQuadraticPart() const noexcept {
		return getAttenuation().z;
	}
	inline AttenuatibleLight& setConstantPart(float val) noexcept {
		glm::vec3 attenuation = getAttenuation();
		attenuation.x = val;
		return setAttenuation(attenuation);
	}
	inline AttenuatibleLight& setLinearPart(float val) noexcept {
		glm::vec3 attenuation = getAttenuation();
		attenuation.y = val;
		return setAttenuation(attenuation);
	}
	inline AttenuatibleLight& setQuadraticPart(float val) noexcept {
		glm::vec3 attenuation = getAttenuation();
		attenuation.z = val;
		return setAttenuation(attenuation);
	}
	inline AttenuatibleLight& updateConstantPart(float update) noexcept {
		return setConstantPart(getConstantPart() + update);
	}
	inline AttenuatibleLight& updateLinearPart(float update) noexcept {
		return setLinearPart(getLinearPart() + update);
	}
	inline AttenuatibleLight& updateQuadraticPart(float update) noexcept {
		return setQuadraticPart(getQuadraticPart() + update);
	}
};

#endif