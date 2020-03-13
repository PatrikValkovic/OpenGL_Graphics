#include "HouseModel.h"

#include <iostream>
#include <gtc/type_ptr.hpp>

using namespace std;

static const float vertices[] = {
	// positions			// colors			// brick texture	// root textures
	 -0.5f, -0.5f,  0.5f,	1.0f,0.0f,0.0f,		0.0f,  0.0f,		0.0f, -1.0f,
	  0.5f, -0.5f,  0.5f,	0.0f,1.0f,0.0f,		5.0f,  0.0f,		0.0f, -1.0f,
	  0.5f, -0.5f, -0.5f,	0.0f,0.0f,1.0f,		0.0f,  0.0f,		0.0f, -1.0f,
	 -0.5f, -0.5f, -0.5f,	1.0f,1.0f,1.0f,		5.0f,  0.0f,		0.0f, -1.0f,
	 -0.5f,  0.5f,  0.5f,	1.0f,0.0f,0.0f,		0.0f,  5.0f,		0.0f,  0.0f,
	  0.5f,  0.5f,  0.5f,	0.0f,1.0f,0.0f,		5.0f,  5.0f,		0.0f,  0.0f,
	  0.5f,  0.5f, -0.5f,	0.0f,0.0f,1.0f,		0.0f,  5.0f,		2.0f,  0.0f,
	 -0.5f,  0.5f, -0.5f,	1.0f,1.0f,1.0f,		5.0f,  5.0f,		2.0f,  0.0f,
	  0.0f,  0.8f,  0.5f,	0.0f,0.0f,0.0f,		0.0f, 20.0f,		0.0f,  2.0f, 
	  0.0f,  0.8f, -0.5f,	0.0f,0.0f,0.0f,		0.0f, 20.0f,		2.0f,  2.0f
};

static const unsigned int indices[] = {
			0, 1, 2, 0, 2, 3,
			0, 1, 5, 0, 5, 4,
			0, 3, 4, 3, 4, 7,
			3, 2, 7, 7, 2, 6,
			1, 2, 5, 2, 5, 6,
			4, 5, 8, 7, 6, 9,
			5, 6, 8, 6, 8, 9,
			4, 7, 8, 8, 7, 9
};

HouseModel::HouseModel(GLuint wallTexture, GLuint roofTexture) :
	_vertexArray(glDeleteVertexArrays, glGenVertexArrays),
	_elementBuffer(glDeleteBuffers, glGenBuffers),
	_vertexBuffer(glDeleteBuffers, glGenBuffers),
	_wallTexture(wallTexture),
	_roofTexture(roofTexture)
{
	// fill vertices
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// fill element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// fill VAO
	glBindVertexArray(_vertexArray); // bind VAO
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer); // active vertex buffer
	// setup position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), reinterpret_cast<void*>(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	// setup color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// setup wall texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// setup roof texture coords
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), reinterpret_cast<void*>(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
	// use element buffer for rendering
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);

	glBindVertexArray(0); // unbind VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind EBO - must be after unbind of VAO, otherwise is unbinded in VAO as well
}

void HouseModel::render(GLuint program, glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	// attach program
	glUseProgram(program);

	// get sampler locations
	static bool locationsLoaded = false;
	static GLint _wallSampler = -1;
	static GLint _roofSampler = -1;
	static GLint _transformation = -1;
	if (!locationsLoaded) {
		_wallSampler = glGetUniformLocation(program, "wallTexture");
		if (_wallSampler == -1) {
			cerr << "wallTexture uniform variable not found" << endl;
		}
		_roofSampler = glGetUniformLocation(program, "roofTexture");
		if (_roofSampler == -1) {
			cerr << "roofTexture uniform variable not found" << endl;
		}
		_transformation = glGetUniformLocation(program, "transformation");
		if (_transformation == -1) {
			cerr << "transformation uniform variable not found" << endl;
		}
		locationsLoaded = true;
	}
	
	// attach textures
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _wallTexture);
	glUniform1i(_wallSampler, 1);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, _roofTexture);
	glUniform1i(_roofSampler, 7);
	//glBindTexture(GL_TEXTURE_2D, 0); cant unbind because its deactivate it

	// set transformations
	glm::mat4 final_rotation = projection * view * model;
	glUniformMatrix4fv(
		_transformation, // location of variable to modify
		1, // number of matrices to change (in case the uniform variable is array of matrices)
		GL_FALSE, // whether to transpose data
		glm::value_ptr(final_rotation)
		);

	// render
	glBindVertexArray(_vertexArray); // bind VAO
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(float), GL_UNSIGNED_INT, nullptr); // render
	glBindVertexArray(0); // unbind VAO
}
