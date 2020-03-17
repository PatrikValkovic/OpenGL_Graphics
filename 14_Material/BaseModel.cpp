#include "BaseModel.h"
#include <iostream>
#include <gtc/type_ptr.hpp>

BaseModel::BaseModel():
	_vertexBuffer(glDeleteBuffers, glGenBuffers), 
	_vertexArray(glDeleteVertexArrays, glGenVertexArrays)
{}

void BaseModel::_render(GLuint program, std::function<void()> render)
{
	// attach program
	glUseProgram(program);
	
	// attach vertex array
	glBindVertexArray(_vertexArray);
	render();
	glBindVertexArray(0);
}
