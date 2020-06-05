#include "MirrorPaneModel.h"

float vertices[] = {
	// positions
	 37.598f,	0.0f,	 45.831f,
	 23.226f,	0.0f,	 60.395f,
	-23.226f,	0.0f,	 60.395f,
	-37.598f,	0.0f,	 45.831f,
	-37.598f,	0.0f,	-45.831f,
	-23.226f,	0.0f,	-60.395f,
	 23.226f,	0.0f,	-60.395f,
	 37.598f,	0.0f,	-45.831f,
};

unsigned int indices[] = {
	0, 1, 2, 0, 2,3,
	6, 7, 4, 6, 4, 5,
	7, 3, 4, 7, 0, 3
};


MirrorPaneModel::MirrorPaneModel()
{
	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	// fill data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// setup position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MirrorPaneModel::render(GLuint program)
{
	this->_render(
		program,
		[]() {
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
		}
	);
}