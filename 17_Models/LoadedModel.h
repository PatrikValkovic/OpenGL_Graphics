#ifndef __LOADED_MODEL_H__
#define __LOADED_MODEL_H__
#include <vector>
#include <glad/glad.h>
#include "BaseModel.h"

class LoadedModel :	public BaseModel
{
private:
	struct Vertex {
		glm::vec3 position;
	};
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;

	GLuint _vertexBuffer;
	GLuint _vertexArray;
	GLuint _indexBuffer;
public:
	LoadedModel(const char* filename, GLuint program);

	virtual void render(GLuint program) const;
};

#endif