#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <glad/glad.h>
#include <glm.hpp>

class Renderable
{
public:
	Renderable() = default;
	Renderable(const Renderable&) = default;
	Renderable(Renderable&&) = default;
	Renderable& operator=(const Renderable&) = default;
	Renderable& operator=(Renderable&&) = default;
	virtual ~Renderable() = default;

	virtual void render(GLuint program) const = 0;
};

#endif