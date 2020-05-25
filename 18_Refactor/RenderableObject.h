#ifndef __RENDERABLE_OBJECT_H__
#define __RENDERABLE_OBJECT_H__
#include <memory>
#include <glm.hpp>
#include "WrapRenderable.h"
#include "BaseObject.h"
#include "UniformWrapper.h"

class RenderableObject : public WrapRenderable, public BaseObject
{
public:
	RenderableObject();
	RenderableObject(
		Renderable* renderable,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::mat3 rotate = glm::mat3(1.0f)
	);

	RenderableObject(const RenderableObject&) = default;
	RenderableObject(RenderableObject&&) = default;
	RenderableObject& operator=(const RenderableObject&) = default;
	RenderableObject& operator=(RenderableObject&&) = default;
	virtual ~RenderableObject() = default;

	virtual void render(GLuint program, glm::mat4 model);
	virtual void render(GLuint program) override;
};

class RenderableObjectDestroy : public RenderableObject
{
public:
	RenderableObjectDestroy() = default;
	RenderableObjectDestroy(
		Renderable* renderable,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::mat3 rotate = glm::mat3(1.0f)
	);
	RenderableObjectDestroy(const RenderableObjectDestroy&) = delete;
	RenderableObjectDestroy(RenderableObjectDestroy&&) = default;
	RenderableObjectDestroy& operator=(const RenderableObjectDestroy&) = delete;
	RenderableObjectDestroy& operator=(RenderableObjectDestroy&&) = default;
	virtual ~RenderableObjectDestroy();
};






#endif