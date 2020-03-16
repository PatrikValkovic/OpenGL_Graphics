#ifndef __BASE_LIGHT_H__
#define __BASE_LIGHT_H__

#include <glm.hpp>
#include <algorithm>

class BaseLight
{
protected:
	float _lightStrength;
	glm::vec3 _lightColor;
	BaseLight(float strength = 0.1f, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
public:
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

	inline glm::vec3 getColor() const noexcept {
		return _lightColor;
	}

	inline void setColor(glm::vec3 color) noexcept {
		_lightColor = glm::max(glm::vec3(0.0f), glm::min(glm::vec3(1.0f), color));
	}

	inline void updateColor(glm::vec3 amount) noexcept {
		this->setColor(this->getColor() + amount);
	}

	inline void updateRed(float amount) noexcept {
		this->updateColor(glm::vec3(amount, 0.0f, 0.0f));
	}

	inline void updateGreen(float amount) noexcept {
		this->updateColor(glm::vec3(0.0f, amount, 0.0f));
	}

	inline void updateBlue(float amount) noexcept {
		this->updateColor(glm::vec3(0.0f, 0.0f, amount));
	}
};

#endif