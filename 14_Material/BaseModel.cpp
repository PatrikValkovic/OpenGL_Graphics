#include "BaseModel.h"
#include <iostream>
#include <gtc/type_ptr.hpp>

BaseModel::BaseModel():
	_vertexBuffer(glDeleteBuffers, glGenBuffers), 
	_vertexArray(glDeleteVertexArrays, glGenVertexArrays)
{}

void BaseModel::transformations(GLuint program, glm::mat4* model, glm::mat4* view, glm::mat4* projection)
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

void BaseModel::_render(GLuint program, std::function<void()> render, glm::mat4 *model, glm::mat4 *view, glm::mat4 *projection)
{
	// attach program
	glUseProgram(program);

	// pass transformation matrices
	BaseModel::transformations(program, model, view, projection);
	
	// attach vertex array
	glBindVertexArray(_vertexArray);
	render();
	glBindVertexArray(0);
}
