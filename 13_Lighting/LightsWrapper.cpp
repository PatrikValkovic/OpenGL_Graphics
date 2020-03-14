#include "LightsWrapper.h"

void LightsWrapper::clear()
{
	_lights.clear();
}

void LightsWrapper::addLight(LightObject &light)
{
	_lights.push_back(&light);
}

void LightsWrapper::updateRendering(GLuint program)
{
	glUseProgram(program);

	glm::vec3 pos = _lights[0]->getPosition();
	glm::vec3 color = _lights[0]->getColor();
	float strength = _lights[0]->getStrength();

	glUniform3f(glGetUniformLocation(program, "light_pos"), pos.x, pos.y, pos.z);
	glUniform3f(glGetUniformLocation(program, "light_color"), color.x, color.y, color.z);
	glUniform1f(glGetUniformLocation(program, "light_strength"), strength);
}
