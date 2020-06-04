#include <glm.hpp>
#ifndef __BASE_CAMERA_H__
#define __BASE_CAMERA_H__

class BaseCamera
{
public:
	virtual ~BaseCamera();

	virtual void move(glm::vec3 direction) noexcept = 0;
	virtual void look(glm::vec2 direction) noexcept = 0;
	virtual void rotate(float degree) noexcept = 0;
	virtual glm::mat4 createTransformMatrix() const noexcept = 0;

	virtual glm::vec3 getPos() const noexcept = 0;
	virtual glm::vec3 getViewDirection() const noexcept = 0;
	virtual glm::vec3 getCameraUp() const noexcept = 0;


	void moveX(float distance) noexcept;
	void moveY(float distance) noexcept;
	void moveZ(float distance) noexcept;

	void lookUp(float degree) noexcept;
	void lookDown(float degree) noexcept;
	void lookLeft(float degree) noexcept;
	void lookRight(float degree) noexcept;

	void rotateLeft(float degree) noexcept;
	void rotateRight(float degree) noexcept;

};

#endif