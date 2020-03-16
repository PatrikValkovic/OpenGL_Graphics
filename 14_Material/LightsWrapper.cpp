#include "LightsWrapper.h"

void LightsWrapper::clear()
{
	_lights.clear();
}

void LightsWrapper::addLight(LightObject &light)
{
	_lights.push_back(&light);
}

void LightsWrapper::updateRendering(GLuint program, BaseCamera& camera)
{
	glUseProgram(program);

	glm::vec3 camera_dir = camera.getViewDirection();
	glm::vec3 pos = _lights[0]->getPosition();
	glm::vec3 color = _lights[0]->getColor();
	float strength = _lights[0]->getStrength();
	float specular = _lights[0]->getSpecularStrength();
	unsigned int reflectness = _lights[0]->getReflectness();

	glUniform3f(glGetUniformLocation(program, "light_pos"), pos.x, pos.y, pos.z);
	glUniform3f(glGetUniformLocation(program, "light_color"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, "camera_view_direction"), camera_dir.x, camera_dir.y, camera_dir.z);
	glUniform1f(glGetUniformLocation(program, "light_strength"), strength);
	glUniform1f(glGetUniformLocation(program, "ligh_specular_strength"), specular);
	glUniform1ui(glGetUniformLocation(program, "ligh_reflectness"), reflectness);
}
