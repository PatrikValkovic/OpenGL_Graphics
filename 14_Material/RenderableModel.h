#ifndef __RENDERABLE_MODEL_H__
#define __RENDERABLE_MODEL_H__

#include "RenderableObject.h"
#include "BaseModel.h"

class RenderableModel : public RenderableObject
{
private:
	BaseModel &_model;
public:
	RenderableModel(
		BaseModel& model,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotate = glm::vec3(0.0f)
	);

	virtual void render(GLuint program, glm::mat4* model = nullptr, glm::mat4* view = nullptr, glm::mat4* projection = nullptr) override;
};

#endif