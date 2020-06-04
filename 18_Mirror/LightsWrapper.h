#ifndef __LIGHTS_WRAPPER_H__
#define __LIGHTS_WRAPPER_H__

#include <vector>
#include <glad/glad.h>
#include "LightObject.h"
#include "BaseCamera.h"
#include "RAII.h"
#include "UniformWrapper.h"
#include "SharedProgram.h"

class LightsWrapper
{
protected:
	static UniformWrapper _uniform;
	std::vector<LightObject*> _lights;
	RAIIArray<> _ssbo;
public:
	LightsWrapper();
	LightsWrapper(const LightsWrapper&) = default;
	LightsWrapper(LightsWrapper&&) = default;
	LightsWrapper& operator=(const LightsWrapper&) = default;
	LightsWrapper& operator=(LightsWrapper&&) = default;
	~LightsWrapper() = default;

	void clear();
	void addLight(LightObject* light);

	void updateRendering(GLuint program, BaseCamera &camera, bool verbose=true);
};


class LightsWrapperDestroy : public LightsWrapper
{
public:
	LightsWrapperDestroy() = default;
	LightsWrapperDestroy(const LightsWrapper&) = delete;
	LightsWrapperDestroy(LightsWrapperDestroy&&) = default;
	LightsWrapperDestroy& operator=(const LightsWrapperDestroy&) = delete;
	LightsWrapperDestroy& operator=(LightsWrapperDestroy&&) = default;
	~LightsWrapperDestroy();
};



#endif