#ifndef __CAMERA_H__
#define __CAMERA_H_

#include <glm.hpp>

class Camera
{
private:
	glm::vec3 _position;
	glm::vec3 _view_direction;
	glm::vec3 _up;
public:
	Camera() noexcept;
	void move(glm::vec3 direction) noexcept;
	void moveX(float distance) noexcept;
	void moveY(float distance) noexcept;
	void moveZ(float distance) noexcept;

	void rotate(float degree) noexcept;

	glm::mat4 createTransformMatrix() const noexcept;
};

#endif