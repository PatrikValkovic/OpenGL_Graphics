#ifndef __HOUSE_MODEL__H_
#define __HOUSE_MODEL__H_

#include <glad/glad.h>
#include <glm.hpp>
#include "RAII.h"
#include "BaseModel.h"

class HouseModel : public BaseModel
{
private:
	RAIIArray<> _elementBuffer;
	GLuint _wallTexture;
	GLuint _roofTexture;
public:
	HouseModel(GLuint wallTexture, GLuint roofTexture);

	virtual void render(GLuint program, glm::mat4* model = nullptr, glm::mat4* view = nullptr, glm::mat4* projection = nullptr);
};

#endif