#ifndef __BASE_MODEL_H__
#define __BASE_MODEL_H__

#include <functional>
#include <glad/glad.h>
#include <glm.hpp>
#include "Renderable.h"
#include "RAII.h"


class BaseModel : public Renderable
{
protected:
	RAIIArray<> _vertexBuffer;
	RAIIArray<> _vertexArray;
	void _render(GLuint program, std::function<void()> render) const;
public:
	BaseModel();
	virtual ~BaseModel() = default;
};

#endif