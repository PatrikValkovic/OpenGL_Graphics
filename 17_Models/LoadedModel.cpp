#include "LoadedModel.h"


ModelNodeDefinition::ModelNodeDefinition(meshes_vector&& meshes, children_vector&& children)
	: meshes(std::move(meshes)), children(std::move(children))
{}

void ModelNodeDefinition::render(GLuint program)
{
	for (auto& child : children)
		child->render(program);

	for (auto& mesh : meshes)
		mesh->render(program);
}
