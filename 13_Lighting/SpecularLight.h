#ifndef __SPECULAR_LIGHT_H__
#define __SPECULAR_LIGHT_H__

#include "BaseLight.h"

class SpecularLight: public BaseLight
{
protected:
	float _specularStrength;
	unsigned int _reflectness;
public:
	SpecularLight(
		float lightStrength = 0.1f, 
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), 
		float specularStrength = 0.0f, 
		unsigned int reflectness = 0
	);

	inline float getSpecularStrength() const noexcept {
		return _specularStrength;
	}

	inline void setSpecularStrength(float strength) noexcept {
		_specularStrength = std::max(0.0f, std::min(1.0f, strength));
	}

	inline void updateSpecularStrength(float amount) noexcept {
		this->setSpecularStrength(this->getSpecularStrength() + amount);
	}

	inline unsigned int getReflectness() const noexcept {
		return _reflectness;
	}

	inline void setReflectness(unsigned int new_value) noexcept {
		_reflectness = new_value;
	}

	inline void updateReflectness(int amount) noexcept {
		this->setReflectness(this->getReflectness() + amount);
	}
};

#endif