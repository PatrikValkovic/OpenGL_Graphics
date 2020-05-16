#ifndef __SPOTLIGHT_H__
#define __SPOTLIGHT_H__
#include <cassert>
#include <glm.hpp>
#include "DirectionalLight.h"
#include "AttenuatibleLight.h"

class Spotlight : public DirectionalLight, public AttenuatibleLight
{
private:
	float _innerCutoff;
	float _outerCutoff;
public:
	Spotlight(
		float innerCutoff=30.0f,
		float outerCufoff=45.0f,
		glm::vec3 direction = glm::vec3(0.0, -1.0, 0.0),
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3 attenuation = glm::vec3(1, 0.14, 0.07),
		float strength = 1.0
	);
	Spotlight(const Spotlight&) = default;
	Spotlight(Spotlight&&) = default;
	Spotlight& operator=(const Spotlight&) = default;
	Spotlight& operator=(Spotlight&&) = default;


	inline float getInnerCutoff() const noexcept {
		return _innerCutoff;
	}
	inline float getOuterCutoff() const noexcept {
		return _outerCutoff;
	}
	inline Spotlight& setInnerCutoff(float cutoff) noexcept {
		_innerCutoff = cutoff;
		assert((_innerCutoff < _outerCutoff));
		return *this;
	}
	inline Spotlight& setOuterCutoff(float cutoff) noexcept {
		_outerCutoff = cutoff;
		assert((_innerCutoff < _outerCutoff));
		return *this;
	}
	inline Spotlight& updateInnerCutoff(float update) noexcept {
		return this->setInnerCutoff(this->getInnerCutoff() + update);
	}
	inline Spotlight& updateOuterCutoff(float update) noexcept {
		return this->setOuterCutoff(this->getOuterCutoff() + update);
	}


	virtual unsigned int getType() const noexcept;

	virtual int getParameters(float parameters[8]) const noexcept;
};

#endif