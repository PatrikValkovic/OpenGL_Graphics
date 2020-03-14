#ifndef __AMBIENT_LIGHT_H__
#define __AMBIENT_LIGHT_H__

#include <glad/glad.h>
#include "BaseLight.h"

class AmbientLight : public BaseLight
{
public:
	AmbientLight(float strength = 0.1f, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
	void use(GLuint program) const;
	void printInfo() const noexcept;
};

#endif