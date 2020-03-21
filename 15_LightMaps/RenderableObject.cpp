#include "RenderableObject.h"
#include <iostream>
#include <gtx/transform.hpp>
#include <gtx/euler_angles.hpp>
#include <gtc/type_ptr.hpp>

RenderableObject::RenderableObject(glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: Transformable(translate, scale, rotate), _renderable(nullptr)
{}


RenderableObject::RenderableObject(const Renderable &renderable, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: Transformable(translate, scale, rotate), _renderable(&renderable)
{}

void RenderableObject::render(GLuint program) const
{
	this->render(program, glm::mat4(1.0f), nullptr, nullptr);
}

void RenderableObject::render(GLuint program, glm::mat4 model, glm::mat4* view, glm::mat4* projection) const
{
	if (this->_renderable == nullptr)
		return;

	glm::mat4 my_transform = model * glm::translate(_position) * glm::yawPitchRoll(
		glm::radians(_rotate.y),
		glm::radians(_rotate.x),
		glm::radians(_rotate.z)
	) * glm::scale(_scale);

	RenderableObject::transformations(program, &my_transform, view, projection);

	_renderable->render(program);
}

void RenderableObject::transformations(GLuint program, glm::mat4* model, glm::mat4* view, glm::mat4* projection)
{
	using namespace std;
	glUseProgram(program);
	// get sampler locations
	GLint _modelMatrix = -1;
	GLint _viewMatrix = -1;
	GLint _projectionMatrix = -1;
	_modelMatrix = glGetUniformLocation(program, "model");
	if (_modelMatrix == -1) {
		cerr << "model uniform variable not found" << endl;
	}
	_viewMatrix = glGetUniformLocation(program, "view");
	if (_viewMatrix == -1) {
		cerr << "view uniform variable not found" << endl;
	}
	_projectionMatrix = glGetUniformLocation(program, "projection");
	if (_projectionMatrix == -1) {
		cerr << "projection uniform variable not found" << endl;
	}

	// fill matrices
	if (model != nullptr)
		glUniformMatrix4fv(
			_modelMatrix, // location of variable to modify
			1, // number of matrices to change (in case the uniform variable is array of matrices)
			GL_FALSE, // whether to transpose data
			glm::value_ptr(*model) // value to store
		);
	if (view != nullptr)
		glUniformMatrix4fv(_viewMatrix, 1, GL_FALSE, glm::value_ptr(*view));
	if (projection != nullptr)
		glUniformMatrix4fv(_projectionMatrix, 1, GL_FALSE, glm::value_ptr(*projection));
}
