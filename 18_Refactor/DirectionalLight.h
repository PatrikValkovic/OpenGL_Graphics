#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__
#include <glm.hpp>
#include "BaseLight.h"


class DirectionalLight : public	BaseLight	
{
private:
	glm::vec3 _direction;
public:
	DirectionalLight(
		glm::vec3 direction = glm::vec3(0.0, -1.0, 0.0),
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
		float strength = 1.0
	);
	DirectionalLight(const DirectionalLight&) = default;
	DirectionalLight(DirectionalLight&&) = default;
	DirectionalLight& operator=(const DirectionalLight&) = default;
	DirectionalLight& operator=(DirectionalLight&&) = default;

	virtual glm::vec3 getDirection() const noexcept override;
	inline DirectionalLight& setDirection(glm::vec3 direction) noexcept {
		_direction = direction;
		return *this;
	}
	inline DirectionalLight& updateDirection(glm::vec3 update) noexcept {
		return this->setDirection(this->getDirection() + update);
	}

	virtual unsigned int getType() const noexcept override;

	virtual int getParameters(float parameters[8]) const noexcept override;
};


#endif