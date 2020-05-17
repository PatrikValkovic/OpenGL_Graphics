#ifndef __SIM_CAMERA_H__
#define __SIM_CAMERA_H_

#include <glm.hpp>
#include "BaseCamera.h"

class SimCamera : public BaseCamera
{
private:
	glm::vec3 _position;
	glm::vec3 _view_direction;
	glm::vec3 _up;
public:
	SimCamera(
		glm::vec3 position = glm::vec3(0, 0, 0), 
		glm::vec3 view_direction = glm::vec3(0, 0, -1),
		glm::vec3 camera_up = glm::vec3(0, 1, 0)
	) noexcept;
	
	virtual void move(glm::vec3 direction) noexcept;

	virtual void look(glm::vec2 direction) noexcept;

	virtual void rotate(float degree) noexcept;

	virtual glm::mat4 createTransformMatrix() const noexcept;


	virtual inline glm::vec3 getPos() const noexcept;
	virtual inline glm::vec3 getViewDirection() const noexcept;
	virtual glm::vec3 getCameraUp() const noexcept;
};

#endif