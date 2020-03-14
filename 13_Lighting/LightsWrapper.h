#ifndef __LIGHTS_WRAPPER_H__
#define __LIGHTS_WRAPPER_H__

#include <vector>
#include <glad/glad.h>
#include "LightObject.h"
#include "BaseCamera.h"


class LightsWrapper
{
private:
	std::vector<LightObject*> _lights;
public:
	void clear();
	void addLight(LightObject &light);

	void updateRendering(GLuint program, BaseCamera &camera);
};

#endif