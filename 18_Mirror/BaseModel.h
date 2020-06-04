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
	virtual void _render(GLuint program, std::function<void()> render) const;
public:
	BaseModel();
	BaseModel(const BaseModel&) = delete;
	BaseModel(BaseModel&&) = default;
	BaseModel& operator=(const BaseModel&) = delete;
	BaseModel& operator=(BaseModel&&) = default;
	virtual ~BaseModel() = default;
};

#endif