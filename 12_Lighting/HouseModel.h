#ifndef __HOUSE_MODEL__H_
#define __HOUSE_MODEL__H_

#include <glad/glad.h>
#include <glm.hpp>
#include "RAII.h"

class HouseModel
{
private:
	RAIIArray<> _vertexArray;
	RAIIArray<> _elementBuffer;
	RAIIArray<> _vertexBuffer;
	GLuint _wallTexture;
	GLuint _roofTexture;
public:
	HouseModel(GLuint wallTexture, GLuint roofTexture);

	void render(GLuint program, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
};

#endif