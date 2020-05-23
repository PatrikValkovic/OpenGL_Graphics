#ifndef __AMBIENT_LIGHT_H__
#define __AMBIENT_LIGHT_H__

#include <glad/glad.h>
#include "BaseLight.h"
#include "UniformWrapper.h"

class AmbientLight : public BaseLight
{
private:
	UniformWrapper _uniform;
public:
	AmbientLight(float strength = 0.1f, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
	void use(GLuint program);
	void printInfo() const noexcept;

	virtual unsigned int getType() const noexcept override;
};

#endif