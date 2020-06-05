#include "LightsWrapper.h"
#include <iostream>
#include "Constants.h"

UniformWrapper LightsWrapper::_uniform;

LightsWrapper::LightsWrapper()
	: _lights(), _ssbo(glDeleteBuffers, glGenBuffers)
{}

void LightsWrapper::clear()
{
	_lights.clear();
}

void LightsWrapper::addLight(LightObject* light)
{
	_lights.push_back(std::move(light));
}

void LightsWrapper::updateRendering(GLuint program, BaseCamera& camera, bool verbose)
{
	// use program
	glUseProgram(program);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, _ssbo);
	size_t elementsize = int(std::ceil((float)sizeof(LightDefinition) / (float)sizeof(glm::vec4))) * sizeof(glm::vec4);
	size_t buffersize = elementsize * _lights.size();
	std::vector<GLbyte> buffer(buffersize);
	GLbyte* write_ptr = buffer.data();
	for (LightObject* lightobj : _lights) {
		LightDefinition def;
		def.type = lightobj->getLight().getType();
		def.position = glm::vec4(lightobj->getPosition(), 0);
		glm::mat4 transform_matrix = lightobj->transformMatrix();
		glm::vec4 direction = glm::vec4(lightobj->getLight().getDirection(), 0.0);
		def.direction = glm::vec4(glm::vec3(transform_matrix * direction), 0);
		def.color = glm::vec4(lightobj->getLight().getColor(), 0);
		lightobj->getLight().getParameters(def.parameters);
		std::memcpy(write_ptr, &def, sizeof(LightDefinition));
		write_ptr += elementsize;
	}
	glBufferData(GL_SHADER_STORAGE_BUFFER, buffersize, buffer.data(), GL_DYNAMIC_DRAW);

	// fill info about camera
	glm::vec3 camera_dir = camera.getViewDirection();
	GLint camera_view_direction_pos = _uniform(program, "camera_view_direction");
	glUniform3f(camera_view_direction_pos, camera_dir.x, camera_dir.y, camera_dir.z);
}

LightsWrapperDestroy::~LightsWrapperDestroy()
{
	if (VERBOSE) {
		std::cout << "Destroying LightsWrapper " << this << std::endl;
	}
	for (LightObject* lightobj : _lights)
		delete lightobj;
}
