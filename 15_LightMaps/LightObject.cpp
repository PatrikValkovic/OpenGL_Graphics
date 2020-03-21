#include "LightObject.h"



LightObject::LightObject(const PointLight& light)
	: RenderableObject(), _light(light)
{}

LightObject::LightObject(const PointLight& light, const Renderable& inner)
	: RenderableObject(inner), _light(light)
{}

void LightObject::render(GLuint program) const
{
	RenderableObject::render(program);
}
