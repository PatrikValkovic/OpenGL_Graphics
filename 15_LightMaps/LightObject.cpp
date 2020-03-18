#include "LightObject.h"

LightObject::LightObject(
	SpotLight& light,
	Renderable* model
	) : RenderableObject(model), _light(light)
{}

void LightObject::render(GLuint program)
{
	RenderableObject::render(program);
}
