#include "LightsWrapper.h"
#include <iostream>

void LightsWrapper::clear()
{
	_lights.clear();
}

void LightsWrapper::addLight(LightObject &light)
{
	_lights.push_back(&light);
}

void LightsWrapper::updateRendering(GLuint program, BaseCamera& camera, bool verbose)
{

	using namespace std;

	glm::vec3 pos = _lights[0]->getPosition();
	glm::vec3 color = _lights[0]->getLight().getColor();
	float light_distance = _lights[0]->getLight().getDistance();
	float strength = _lights[0]->getLight().getStrength();
	glm::vec3 camera_dir = camera.getViewDirection();

	glUseProgram(program);

	GLint position_loc = glGetUniformLocation(program, "light.position");
	if (position_loc == -1 && verbose) {
		cerr << "light.position uniform variable not found" << endl;
	}
	glUniform3f(position_loc, pos.x, pos.y, pos.z);

	GLint color_loc = glGetUniformLocation(program, "light.color");
	if (color_loc == -1 && verbose) {
		cerr << "light.color uniform variable not found" << endl;
	}
	glUniform3f(color_loc, color.x, color.y, color.z);

	GLint distance_loc = glGetUniformLocation(program, "light.distanceCoeficient");
	if (distance_loc == -1 && verbose) {
		cerr << "light.distanceCoeficient uniform variable not found" << endl;
	}
	glUniform1f(distance_loc, light_distance);

	GLint strength_loc = glGetUniformLocation(program, "light.strength");
	if (strength_loc == -1 && verbose) {
		cerr << "light.strength uniform variable not found" << endl;
	}
	glUniform1f(strength_loc, strength);

	GLint camera_view_direction_log = glGetUniformLocation(program, "camera_view_direction");
	if (camera_view_direction_log == -1 && verbose) {
		cerr << "camera_view_direction uniform variable not found" << endl;
	}
	glUniform3f(camera_view_direction_log, camera_dir.x, camera_dir.y, camera_dir.z);

}
