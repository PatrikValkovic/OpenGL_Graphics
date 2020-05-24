#ifndef __LIGHTS_WRAPPER_H__
#define __LIGHTS_WRAPPER_H__

#include <vector>
#include <glad/glad.h>
#include "LightObject.h"
#include "BaseCamera.h"
#include "RAII.h"
#include "UniformWrapper.h"
#include "SharedProgram.h"

template<typename PTRTYPE = LightObject*>
class LightsWrapper
{
private:
	std::vector<PTRTYPE> _lights;
	RAIIArray<> _ssbo;
	UniformWrapper _uniform;
public:
	LightsWrapper();
	~LightsWrapper() = default;
	void clear();
	void addLight(PTRTYPE &&light);

	void updateRendering(GLuint program, BaseCamera &camera, bool verbose=true);
};

using LightsWrapperPtr = LightsWrapper<LightObject*>;
using LightsWrapperUniq = LightsWrapper<std::unique_ptr<LightObject>>;
using LightsWrapperShare = LightsWrapper<std::shared_ptr<LightObject>>;

template<typename PTRTYPE>
LightsWrapper<PTRTYPE>::LightsWrapper()
	: _lights(), _ssbo(glDeleteBuffers, glGenBuffers), _uniform()
{}

template<typename PTRTYPE>
void LightsWrapper<PTRTYPE>::clear()
{
	_lights.clear();
}

template<typename PTRTYPE>
void LightsWrapper<PTRTYPE>::addLight(PTRTYPE&& light)
{
	_lights.push_back(std::move(light));
}

template<typename PTRTYPE>
void LightsWrapper<PTRTYPE>::updateRendering(GLuint program, BaseCamera& camera, bool verbose)
{
	// use program
	glUseProgram(program);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, _ssbo);
	size_t elementsize = int(std::ceil((float)sizeof(LightDefinition) / (float)sizeof(glm::vec4))) * sizeof(glm::vec4);
	size_t buffersize = elementsize * _lights.size();
	std::vector<GLbyte> buffer(buffersize);
	GLbyte* write_ptr = buffer.data();
	for (PTRTYPE lightobj : _lights) {
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

#endif