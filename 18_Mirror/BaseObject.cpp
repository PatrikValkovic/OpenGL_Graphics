#include "BaseObject.h"
#include <gtx/transform.hpp>
#include <gtx/euler_angles.hpp>
#include <gtc/type_ptr.hpp>

UniformWrapper BaseObject::_uniform;

BaseObject::BaseObject(glm::vec3 translate, glm::vec3 scale, glm::mat3 rotate)
	: Transformable(translate, scale, rotate)
{}

glm::mat4 BaseObject::transformMatrix() const noexcept
{
	return glm::translate(_position) * glm::mat4(_rotate) * glm::scale(_scale);
}

void BaseObject::transformations(GLuint program, glm::mat4* model, glm::mat4* view, glm::mat4* projection)
{
	using namespace std;
	glUseProgram(program);
	// get sampler locations
	GLint modelMatrix = BaseObject::_uniform(program, "model");
	GLint viewMatrix = BaseObject::_uniform(program, "view");
	GLint projectionMatrix = BaseObject::_uniform(program, "projection");

	// fill matrices
	if (model != nullptr)
		glUniformMatrix4fv(
			modelMatrix, // location of variable to modify
			1, // number of matrices to change (in case the uniform variable is array of matrices)
			GL_FALSE, // whether to transpose data
			glm::value_ptr(*model) // value to store
		);
	if (view != nullptr)
		glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(*view));
	if (projection != nullptr)
		glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, glm::value_ptr(*projection));
}