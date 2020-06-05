#include "AmbientLight.h"
#include <iostream>


AmbientLight::AmbientLight(float strength, glm::vec3 color)
	: BaseLight(strength, color), _uniform()
{}

void AmbientLight::use(GLuint program)
{
	// set strength
	GLint ambientStrengthLocation = _uniform(program, "ambient_strength");
	glUniform1f(ambientStrengthLocation, _lightStrength);
	// set color
	GLint ambientColorLocation = _uniform(program, "ambient_color");
	glUniform3f(ambientColorLocation, _color.r, _color.g, _color.b);
}

unsigned int AmbientLight::getType() const noexcept
{
	return 0;
}
