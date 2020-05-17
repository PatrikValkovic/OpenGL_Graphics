#include "AmbientLight.h"
#include <iostream>


AmbientLight::AmbientLight(float strength, glm::vec3 color)
	: BaseLight(strength, color)
{}

void AmbientLight::use(GLuint program) const
{
	glUseProgram(program);
	// set strength
	GLint ambientStrengthLocation = glGetUniformLocation(program, "ambient_strength");
	if (ambientStrengthLocation == -1) {
		std::cerr << "ambient_strength was not found" << std::endl;
	}
	glUniform1f(ambientStrengthLocation, _lightStrength);
	
	// set color
	GLint ambientColorLocation = glGetUniformLocation(program, "ambient_color");
	if (ambientColorLocation == -1) {
		std::cerr << "ambient_color was not found" << std::endl;
	}
	glUniform3f(ambientColorLocation, _color.r, _color.g, _color.b);
}

void AmbientLight::printInfo() const noexcept
{
	using namespace std;
	std::cout << "Ambient: strength(" << _lightStrength << ") color(" << _color.r << "," << _color.g << "," << _color.b << ")" << endl;
}

unsigned int AmbientLight::getType() const noexcept
{
	return 0;
}
