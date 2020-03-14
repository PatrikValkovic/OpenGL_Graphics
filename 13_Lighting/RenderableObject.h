#ifndef __RENDERABLE_OBJECT_H__
#define __RENDERABLE_OBJECT_H__

#include <glm.hpp>
#include "Renderable.h"


class RenderableObject : public Renderable
{
protected:
	glm::vec3 _scale;
	glm::vec3 _rotate;
	glm::vec3 _translate;
public:
	RenderableObject(
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotate = glm::vec3(0.0f)
	);

	RenderableObject(const RenderableObject&) = default;
	RenderableObject(RenderableObject&&) = default;
	RenderableObject& operator=(const RenderableObject&) = default;
	RenderableObject& operator=(RenderableObject&&) = default;
	virtual ~RenderableObject() = default;

	RenderableObject& moveTo(glm::vec3 where) noexcept;
	RenderableObject& moveBy(glm::vec3 by) noexcept;
	RenderableObject& moveX(float distance) noexcept;
	RenderableObject& moveY(float distance) noexcept;
	RenderableObject& moveZ(float distance) noexcept;
	RenderableObject& scale(glm::vec3 scale) noexcept;
	RenderableObject& scaleX(float ratio) noexcept;
	RenderableObject& scaleY(float ratio) noexcept;
	RenderableObject& scaleZ(float ratio) noexcept;
	RenderableObject& rotate(glm::vec3 rotation) noexcept;
	RenderableObject& rotateAroundX(float degree) noexcept;
	RenderableObject& rotateAroundY(float degree) noexcept;
	RenderableObject& rotateAroundZ(float degree) noexcept;


	inline glm::vec3 getPosition() const noexcept {
		return _translate;
	}
};

#endif