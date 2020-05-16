#ifndef __RENDERABLE_OBJECT_H__
#define __RENDERABLE_OBJECT_H__

#include <glm.hpp>
#include "Renderable.h"
#include "Transformable.h"


class RenderableObject : public Renderable, public Transformable
{
protected:
	Renderable const * _renderable;
public:
	RenderableObject(
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotate = glm::vec3(0.0f)
		);
	RenderableObject(
		const Renderable &renderable,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotate = glm::vec3(0.0f)
	);


	RenderableObject(const RenderableObject&) = default;
	RenderableObject(RenderableObject&&) = default;
	RenderableObject& operator=(const RenderableObject&) = default;
	RenderableObject& operator=(RenderableObject&&) = default;
	virtual ~RenderableObject() = default;

	virtual void render(GLuint program, glm::mat4 model, glm::mat4* view = nullptr, glm::mat4* projection = nullptr) const;
	virtual void render(GLuint program) const override;
	
	glm::mat4 transformMatrix() const noexcept;

	static void transformations(GLuint program, glm::mat4* model = nullptr, glm::mat4* view = nullptr, glm::mat4* projection = nullptr);
};

#endif