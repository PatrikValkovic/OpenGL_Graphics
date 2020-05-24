#ifndef __RENDERABLE_OBJECT_H__
#define __RENDERABLE_OBJECT_H__
#include <memory>
#include <glm.hpp>
#include "Renderable.h"
#include "BaseObject.h"
#include "UniformWrapper.h"

template<typename PTRTYPE = Renderable>
class RenderableObject : public Renderable, public BaseObject
{
protected:
	PTRTYPE _renderable;
public:
	RenderableObject(
		PTRTYPE &&renderable,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotate = glm::vec3(0.0f)
	);


	RenderableObject(const RenderableObject&) = default;
	RenderableObject(RenderableObject&&) = default;
	RenderableObject& operator=(const RenderableObject&) = default;
	RenderableObject& operator=(RenderableObject&&) = default;
	virtual ~RenderableObject() = default;

	virtual void render(GLuint program, glm::mat4 model);
	virtual void render(GLuint program) override;
};

using RenderableObjectRef = RenderableObject<Renderable&>;
using RenderableObjectPtr = RenderableObject<Renderable*>;
using RenderableObjectUniq = RenderableObject<std::unique_ptr<Renderable>>;
using RenderableObjectShare = RenderableObject<std::shared_ptr<Renderable>>;



template<typename PTRTYPE>
RenderableObject<PTRTYPE>::RenderableObject(PTRTYPE&& renderable, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: BaseObject(translate, scale, rotate), _renderable(std::move(renderable))
{}
template<>
RenderableObject<Renderable&>::RenderableObject(Renderable& renderable, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: BaseObject(translate, scale, rotate), _renderable(renderable)
{}


template<typename PTRTYPE>
void RenderableObject<PTRTYPE>::render(GLuint program)
{
	this->render(program, glm::mat4(1.0f));
}

template<typename PTRTYPE>
void RenderableObject<PTRTYPE>::render(GLuint program, glm::mat4 model)
{
	glm::mat4 my_transform = model * this->transformMatrix();

	BaseObject::transformations(program, &my_transform);

	_renderable->render(program);
}
template<>
void RenderableObject<Renderable&>::render(GLuint program, glm::mat4 model)
{
	glm::mat4 my_transform = model * this->transformMatrix();
	BaseObject::transformations(program, &my_transform);
	_renderable.render(program);
}


#endif