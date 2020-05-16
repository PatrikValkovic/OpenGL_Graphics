#ifndef __TRANSFORMABLE_H__
#define __TRANSFORMABLE_H__

#include <glm.hpp>
#include "Positionable.h"

class Transformable : public Positionable
{
protected:
	glm::vec3 _scale;
	glm::vec3 _rotate;
public:
	Transformable(
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotate = glm::vec3(0.0f)
	);

	Transformable(const Transformable&) = default;
	Transformable(Transformable&&) = default;
	Transformable& operator=(const Transformable&) = default;
	Transformable& operator=(Transformable&&) = default;
	virtual ~Transformable() = default;

	

	inline glm::vec3 getScale() noexcept {
		return _scale;
	}
	inline Transformable& setScale(glm::vec3 scale) {
		this->_scale = scale;
		return *this;
	}
	inline Transformable& scale(glm::vec3 scale) noexcept {
		return this->setScale(this->getScale() + scale);
	}
	inline Transformable& scaleX(float ratio) noexcept {
		return this->scale(glm::vec3(ratio, 0.0f, 0.0f));
	}
	inline Transformable& scaleY(float ratio) noexcept {
		return this->scale(glm::vec3(0.0f, ratio, 0.0f));
	}
	inline Transformable& scaleZ(float ratio) noexcept {
		return this->scale(glm::vec3(0.0f, 0.0f, ratio));
	}


	inline glm::vec3 getRotation() {
		return _rotate;
	}
	inline Transformable& setRotation(glm::vec3 rotation) {
		_rotate = rotation;
		return *this;
	}
	inline Transformable& rotate(glm::vec3 rotation) noexcept {
		return this->setRotation(this->getRotation() + rotation);
	}
	inline Transformable& rotateAroundX(float degree) noexcept {
		return this->rotate(glm::vec3(degree, 0.0f, 0.0f));
	}
	inline Transformable& rotateAroundY(float degree) noexcept {
		return this->rotate(glm::vec3(0.0f, degree, 0.0f));
	}
	inline Transformable& rotateAroundZ(float degree) noexcept {
		return this->rotate(glm::vec3(0.0f, 0.0f, degree));
	}


};


#endif