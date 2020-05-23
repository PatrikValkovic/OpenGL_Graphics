#include "LoadedModel.h"
#include <gtc/type_ptr.hpp>


ModelNodeDefinition::ModelNodeDefinition(meshes_vector&& meshes, children_vector&& children, aiMatrix4x4 t)
	: meshes(std::move(meshes)), children(std::move(children)), 
	transformation(t.a1, t.b1, t.c1, t.d1, t.a2, t.b2, t.c2, t.d2, t.a3, t.b3, t.c3, t.d3, t.a4, t.b4, t.c4, t.d4),
	_modelintern_location(-2)
{}

void ModelNodeDefinition::render(GLuint program)
{
	this->render(program, glm::mat4(1.0));
}

void ModelNodeDefinition::render(GLuint program, glm::mat4 transformation)
{
	glm::mat4 new_transform = transformation * this->transformation;

	for (auto& child : children)
		child->render(program, new_transform);

	if (_modelintern_location == -2) {
		_modelintern_location = glGetUniformLocation(program, "modelintern");
		if (_modelintern_location == -1) {
			std::cerr << "modelintern uniform is not present" << std::endl;
		}
	}

	glUniformMatrix4fv(_modelintern_location, 1, false, glm::value_ptr(new_transform));
	for (auto& mesh : meshes)
		mesh->render(program);
}
