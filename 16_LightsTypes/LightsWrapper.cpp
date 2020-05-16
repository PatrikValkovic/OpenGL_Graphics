#include "LightsWrapper.h"
#include <iostream>
#include <sstream>
#include <gtx/euler_angles.hpp>

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

	unsigned int lighttype = _lights[0]->getLight().getType();
	glm::vec3 pos = _lights[0]->getPosition();
	glm::vec3 color = _lights[0]->getLight().getColor();
	glm::mat4 transform_matrix = _lights[0]->transformMatrix();
	glm::vec4 direction = glm::vec4(_lights[0]->getLight().getDirection(), 0.0);
	glm::vec4 new_direction = transform_matrix * direction;
	glm::vec3 real_direction = glm::vec3(new_direction);
	float parameters[8];
	int num_of_params = _lights[0]->getLight().getParameters(parameters);
	glm::vec3 camera_dir = camera.getViewDirection();

	glUseProgram(program);

	GLint type_loc = glGetUniformLocation(program, "light.type");
	if (type_loc == -1 && verbose) {
		cerr << "light.type uniform variable not found" << endl;
	}
	glUniform1ui(type_loc, lighttype);

	GLint position_loc = glGetUniformLocation(program, "light.position");
	if (position_loc == -1 && verbose) {
		cerr << "light.position uniform variable not found" << endl;
	}
	glUniform3f(position_loc, pos.x, pos.y, pos.z);

	GLint direction_loc = glGetUniformLocation(program, "light.direction");
	if (direction_loc == -1 && verbose) {
		cerr << "light.direction uniform variable not found" << endl;
	}
	glUniform3f(direction_loc, real_direction.x, real_direction.y, real_direction.z);

	GLint color_loc = glGetUniformLocation(program, "light.color");
	if (color_loc == -1 && verbose) {
		cerr << "light.color uniform variable not found" << endl;
	}
	glUniform3f(color_loc, color.x, color.y, color.z);

	for (int i = 0; i < num_of_params; i++) {
		std::stringstream str;
		str << "light.parameters[" << i << "]";
		GLint color_loc = glGetUniformLocation(program, str.str().c_str());
		if (color_loc == -1 && verbose) {
			cerr << str.str() << " uniform variable not found" << endl;
		}
		glUniform1f(color_loc, parameters[i]);
	}

	GLint camera_view_direction_pos = glGetUniformLocation(program, "camera_view_direction");
	if (camera_view_direction_pos == -1 && verbose) {
		cerr << "camera_view_direction uniform variable not found" << endl;
	}
	glUniform3f(camera_view_direction_pos, camera_dir.x, camera_dir.y, camera_dir.z);

}
