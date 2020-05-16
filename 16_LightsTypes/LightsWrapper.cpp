#include "LightsWrapper.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <gtx/euler_angles.hpp>

LightsWrapper::LightsWrapper()
{
	glGenBuffers(1, &_ssbo);
}

void LightsWrapper::clear()
{
	_lights.clear();
}

void LightsWrapper::addLight(LightObject &light)
{
	_lights.push_back(&light);
}

struct LightDefinition {
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;
	GLuint type;
	GLfloat parameters[8];
};

void LightsWrapper::updateRendering(GLuint program, BaseCamera& camera, bool verbose)
{
	// use program
	glUseProgram(program);

	
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, _ssbo);
	size_t buffersize = sizeof(LightDefinition) * _lights.size();
	GLubyte* buffer = new GLubyte[buffersize];
	GLubyte* write = buffer;
	for (LightObject* lightobj : _lights) {
		LightDefinition def;
		def.type = lightobj->getLight().getType();
		def.position = lightobj->getPosition();
		glm::mat4 transform_matrix = lightobj->transformMatrix();
		glm::vec4 direction = glm::vec4(lightobj->getLight().getDirection(), 0.0);
		def.direction = glm::vec3(transform_matrix * direction);
		def.color = lightobj->getLight().getColor();
		lightobj->getLight().getParameters(def.parameters);
		std::memcpy(write, &def, sizeof(LightDefinition));
		write += sizeof(LightDefinition);
	}
	glBufferData(GL_SHADER_STORAGE_BUFFER, buffersize, buffer, GL_DYNAMIC_READ);
	delete buffer;


	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	//glDeleteBuffers(1, &ssbo);

	using namespace std;
	float parameters[8];
	glm::vec3 camera_dir = camera.getViewDirection();
	std::stringstream str;

	// fill number of lights
	/*
	GLint nlights_loc = glGetUniformLocation(program, "n_lights");
	if (nlights_loc == -1 && verbose) {
		cerr << "n_lights uniform variable not found" << endl;
	}
	glUniform1ui(nlights_loc, static_cast<GLuint>(_lights.size()));
	*/

	// fill info about camera
	GLint camera_view_direction_pos = glGetUniformLocation(program, "camera_view_direction");
	if (camera_view_direction_pos == -1 && verbose) {
		cerr << "camera_view_direction uniform variable not found" << endl;
	}
	glUniform3f(camera_view_direction_pos, camera_dir.x, camera_dir.y, camera_dir.z);

	// fill information about lights
	for (int light_i = 0; light_i < 0 /*_lights.size()*/; light_i++) {
		LightObject& lightobj = *_lights[light_i];
		const BaseLight& light = lightobj.getLight();
		unsigned int lighttype = light.getType();
		glm::vec3 pos = lightobj.getPosition();
		glm::mat4 transform_matrix = lightobj.transformMatrix();
		glm::vec4 direction = glm::vec4(light.getDirection(), 0.0);
		glm::vec3 new_direction = glm::vec3(transform_matrix * direction);
		glm::vec3 color = light.getColor();
		int num_of_params = light.getParameters(parameters);
		
		std::stringstream().swap(str);
		str << "lights[" << light_i << "].type";
		GLint type_loc = glGetUniformLocation(program, str.str().c_str());
		if (type_loc == -1 && verbose) {
			cerr << str.str() << " uniform variable not found" << endl;
		}
		glUniform1ui(type_loc, lighttype);

		std::stringstream().swap(str);
		str << "lights[" << light_i << "].position";
		GLint position_loc = glGetUniformLocation(program, str.str().c_str());
		if (position_loc == -1 && verbose) {
			cerr << str.str() << " uniform variable not found" << endl;
		}
		glUniform3f(position_loc, pos.x, pos.y, pos.z);

		std::stringstream().swap(str);
		str << "lights[" << light_i << "].direction";
		GLint direction_loc = glGetUniformLocation(program, str.str().c_str());
		if (direction_loc == -1 && verbose) {
			cerr << str.str() << " uniform variable not found" << endl;
		}
		glUniform3f(direction_loc, new_direction.x, new_direction.y, new_direction.z);

		std::stringstream().swap(str);
		str << "lights[" << light_i << "].color";
		GLint color_loc = glGetUniformLocation(program, str.str().c_str());
		if (color_loc == -1 && verbose) {
			cerr << str.str() << " uniform variable not found" << endl;
		}
		glUniform3f(color_loc, color.x, color.y, color.z);

		for (int param_i = 0; param_i < num_of_params; param_i++) {
			std::stringstream().swap(str);
			str << "lights[" << light_i << "].parameters[" << param_i << "]";
			GLint param_loc = glGetUniformLocation(program, str.str().c_str());
			if (param_loc == -1 && verbose) {
				cerr << str.str() << " uniform variable not found" << endl;
			}
			glUniform1f(param_loc, parameters[param_i]);
		}
	}
}
