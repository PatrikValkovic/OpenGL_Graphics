#ifndef __COMPOSER_OBJECT_H__
#define __COMPOSER_OBJECT_H__
#include <vector>
#include "RenderableObject.h"

class ComposeObject : public RenderableObject
{
protected:
	std::vector<RenderableObject*> _inner;
public:
	ComposeObject() = default;
	ComposeObject(std::vector<RenderableObject*>&& vect);
	ComposeObject(const ComposeObject&) = default;
	ComposeObject(ComposeObject&&) = default;
	ComposeObject& operator=(const ComposeObject&) = default;
	ComposeObject& operator=(ComposeObject&&) = default;
	virtual ~ComposeObject() = default;

	virtual void render(GLuint program, glm::mat4 model) override;

	ComposeObject& addObject(RenderableObject* obj);
};




#endif
