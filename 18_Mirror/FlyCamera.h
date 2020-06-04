#ifndef __FLY_CAMERA_H__
#define __FLY_CAMERA_H__

#include "BaseCamera.h"
#include <glm.hpp>

class FlyCamera : public BaseCamera
{
private:
	glm::vec3 _word_up;
	glm::vec3 _position;
	glm::vec3 _view_direction;
	virtual glm::vec3 getCameraUp() const noexcept;
public:
	FlyCamera(
		glm::vec3 word_up, 
		glm::vec3 position = glm::vec3(0,0,0), 
		glm::vec3 view_direction = glm::vec3(0,0,-1)
	) noexcept;

	virtual void move(glm::vec3 direction) noexcept;
	virtual void look(glm::vec2 direction) noexcept;
	virtual void rotate(float degree) noexcept;
	virtual glm::mat4 createTransformMatrix() const noexcept;

	virtual inline glm::vec3 getPos() const noexcept;
	virtual inline glm::vec3 getViewDirection() const noexcept;
};


#endif