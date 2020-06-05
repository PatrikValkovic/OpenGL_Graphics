#include "ScreenPlaneModel.h"

static const float vertices[] = {
	// positions			// textures coords
	-1.0f, -1.0f,  0.0f,	 0.0f, 0.0f,
	 1.0f, -1.0f,  0.0f,	 1.0f, 0.0f,
	 1.0f,  1.0f,  0.0f,	 1.0f, 1.0f,
	-1.0f,  1.0f,  0.0f,	 0.0f, 1.0f,
};

static const unsigned int indices[] = {
	0,   1,  2,  0,  2,  3,
};

ScreenPlaneModel::ScreenPlaneModel() : ElementBufferModel()
{
	// bind
	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	// fill data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// setup position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ScreenPlaneModel::render(GLuint program)
{
	this->_render(
		program,
		[]() {
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
		}
	);
}
