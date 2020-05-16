#ifndef __COLORABLE_H__
#define __COLORABLE_H__

#include <glm.hpp>

class Colorable
{
protected:
	glm::vec3 _color;
	Colorable(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
public:
	Colorable(const Colorable&) = default;
	Colorable(Colorable&&) = default;
	Colorable& operator=(const Colorable&) = default;
	Colorable& operator=(Colorable&&) = default;
	virtual ~Colorable() = default;


	inline glm::vec3 getColor() const noexcept {
		return _color;
	}
	inline Colorable& setColor(glm::vec3 color) noexcept {
		_color = glm::max(glm::vec3(0.0f), glm::min(glm::vec3(1.0f), color));
		return *this;
	}

	inline Colorable& updateColor(glm::vec3 amount) noexcept {
		return this->setColor(this->getColor() + amount);
	}

	inline Colorable& updateRed(float amount) noexcept {
		return this->updateColor(glm::vec3(amount, 0.0f, 0.0f));
	}

	inline Colorable& updateGreen(float amount) noexcept {
		return this->updateColor(glm::vec3(0.0f, amount, 0.0f));
	}

	inline Colorable& updateBlue(float amount) noexcept {
		return this->updateColor(glm::vec3(0.0f, 0.0f, amount));
	}
};

#endif