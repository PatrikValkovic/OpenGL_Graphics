#include "LightObject.h"



LightObject::LightObject(const BaseLight& light)
	: RenderableObject(), _light(light)
{}

LightObject::LightObject(const BaseLight& light, Renderable& inner)
	: RenderableObject(inner), _light(light)
{}

void LightObject::render(GLuint program)
{
	RenderableObject::render(program);
}
