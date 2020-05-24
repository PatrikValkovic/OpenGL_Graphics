#ifndef __COMPOSER_OBJECT_H__
#define __COMPOSER_OBJECT_H__
#include <vector>
#include "RenderableObject.h"

template<typename PTRTYPE = RenderableObjectVal*>
class ComposeObject : public RenderableObject
{
protected:
	std::vector<PTRTYPE> _inner;
public:
	ComposeObject() = default;
	ComposeObject(std::vector<PTRTYPE>&& vect);
	ComposeObject(const ComposeObject&) = default;
	ComposeObject(ComposeObject&&) = default;
	ComposeObject& operator=(const ComposeObject&) = default;
	ComposeObject& operator=(ComposeObject&&) = default;
	virtual ~ComposeObject() = default;

	virtual void render(GLuint program, glm::mat4 model) override;

	ComposeObject& addObject(PTRTYPE&& obj);
};

template<typename INTERNAL = RenderableObjectRef>
using ComposeObjectPtr = ComposeObject<INTERNAL*>;
template<typename INTERNAL = RenderableObjectRef>
using ComposeObjectUniq = ComposeObject<std::unique_ptr<INTERNAL>>;
template<typename INTERNAL = RenderableObjectRef>
using ComposeObjectShare = ComposeObject<std::shared_ptr<INTERNAL>>;



template<typename PTRTYPE>
ComposeObject<PTRTYPE>::ComposeObject(std::vector<PTRTYPE>&& vect)
	: RenderableObject<PTRTYPE>(), _inner(std::move(vect))
{}

template<typename PTRTYPE>
ComposeObject<PTRTYPE>& ComposeObject<PTRTYPE>::addObject(PTRTYPE&& obj)
{
	_inner.push_back(std::move(obj));
	return *this;
}

template<typename PTRTYPE>
void ComposeObject<PTRTYPE>::render(GLuint program, glm::mat4 model)
{
	glm::mat4 my_transform = model * this->transformMatrix();

	for (PTRTYPE& inner : _inner)
		inner->render(program, my_transform);
}

#endif
