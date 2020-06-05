#ifndef __COMPOSER_OBJECT_H__
#define __COMPOSER_OBJECT_H__
#include <vector>
#include "RenderableObject.h"

class ComposeObject : public RenderableObject
{
protected:
	std::vector<RenderableObject*> _inner;
public:
	ComposeObject();
	ComposeObject(std::vector<RenderableObject*>&& vect);
	ComposeObject(const ComposeObject&) = default;
	ComposeObject(ComposeObject&&) = default;
	ComposeObject& operator=(const ComposeObject&) = default;
	ComposeObject& operator=(ComposeObject&&) = default;
	virtual ~ComposeObject() = default;

	virtual void render(GLuint program, glm::mat4 model) override;
	virtual void render(GLuint program) override;

	ComposeObject& addObject(RenderableObject* obj);
};

class ComposeObjectDestroy : public ComposeObject
{
public:
	ComposeObjectDestroy() = default;
	ComposeObjectDestroy(std::vector<RenderableObject*> && vect);
	ComposeObjectDestroy(const ComposeObjectDestroy&) = delete;
	ComposeObjectDestroy(ComposeObjectDestroy&&) = default;
	ComposeObjectDestroy& operator=(const ComposeObjectDestroy&) = delete;
	ComposeObjectDestroy& operator=(ComposeObjectDestroy&&) = default;
	virtual ~ComposeObjectDestroy();
};




#endif
