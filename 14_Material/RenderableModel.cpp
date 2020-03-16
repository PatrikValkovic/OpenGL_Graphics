#include "RenderableModel.h"
#include <gtx/transform.hpp>
#include <gtx/euler_angles.hpp>


RenderableModel::RenderableModel(BaseModel& model, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: RenderableObject(translate, scale, rotate), _model(model)
{}

void RenderableModel::render(GLuint program, glm::mat4 * model, glm::mat4 * view, glm::mat4 * projection)
{
	glm::mat4 m = glm::mat4(1.0f);
	if (model != nullptr) {
		m = *model;
	}
	glm::mat4 my_transform = m * glm::translate(_translate) * glm::yawPitchRoll(
		glm::radians(_rotate.y),
		glm::radians(_rotate.x),
		glm::radians(_rotate.z)
	) * glm::scale(_scale);

	_model.render(program, &my_transform, view, projection);
}


