#ifndef __CAMERA_H__
#define __CAMERA_H_

#include <glm.hpp>

class Camera
{
private:
	glm::vec3 _position;
public:
	Camera() noexcept;
	void move(glm::vec3 direction) noexcept;
	void moveX(float direction) noexcept;
	void moveY(float direction) noexcept;
	void moveZ(float direction) noexcept;

	glm::mat4 createTransformMatrix() const noexcept;
};

#endif