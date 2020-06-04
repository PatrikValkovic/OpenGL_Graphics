#ifndef __POSITIONABLE_H__
#define __POSITIONABLE_H__

#include <glm.hpp>

class Positionable
{
protected:
	glm::vec3 _position;
public:
	Positionable(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));


	inline glm::vec3 getPosition() const noexcept {
		return _position;
	}
	inline Positionable& setPosition(glm::vec3 position) {
		_position = position;
		return *this;
	}
	inline Positionable& moveTo(glm::vec3 where) noexcept {
		return this->setPosition(where);
	}
	inline Positionable& moveBy(glm::vec3 by) noexcept {
		return this->setPosition(this->getPosition() + by);
	}
	inline Positionable& moveX(float distance) noexcept {
		return this->moveBy(glm::vec3(distance, 0.0f, 0.0f));
	}
	inline Positionable& moveY(float distance) noexcept {
		return this->moveBy(glm::vec3(0.0f, distance, 0.0f));
	}
	inline Positionable& moveZ(float distance) noexcept {
		return this->moveBy(glm::vec3(0.0f, 0.0f, distance));
	}
};

#endif