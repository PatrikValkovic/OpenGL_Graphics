#ifndef __LOADED_MODEL_H__
#define __LOADED_MODEL_H__
#include <iostream>
#include <vector>
#include <memory>
#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "BaseModel.h"
#include "MeshModel.h"
#include "Renderable.h"


class ModelNodeDefinition : public Renderable {
public:
	typedef std::vector<std::unique_ptr<MeshModel>> meshes_vector;
	typedef std::vector<std::unique_ptr<ModelNodeDefinition>> children_vector;
	ModelNodeDefinition(meshes_vector&& meshes, children_vector&& children, aiMatrix4x4 transformation);
	ModelNodeDefinition(ModelNodeDefinition&&) = default;
	ModelNodeDefinition& operator=(ModelNodeDefinition&&) = default;
	virtual ~ModelNodeDefinition() = default;
	meshes_vector meshes;
	children_vector children;
	glm::mat4 transformation;
	GLint _modelintern_location; 
	virtual void render(GLuint program) override;
	virtual void render(GLuint program, glm::mat4 transformation);
};


template<typename NODE_DEFINITION=ModelNodeDefinition>
class LoadedModel :	public Renderable
{
private:
	GLint _use_internode_location;
	std::unique_ptr<NODE_DEFINITION> process_node(const aiNode* node, const aiScene* scene) const;
protected:
	std::unique_ptr<NODE_DEFINITION> _root;
public:
	LoadedModel(const char* filename, GLuint program);

	virtual void render(GLuint program) override;
};





template<typename NODE_DEFINITION>
LoadedModel<NODE_DEFINITION>::LoadedModel(const char* filename, GLuint program)
	: _use_internode_location(-2), _root(nullptr)
{
	std::cout << "Loading model: " << filename << std::endl;
	
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		filename,
		aiPostProcessSteps::aiProcess_Triangulate |
		aiPostProcessSteps::aiProcess_FlipUVs | 
		aiProcess_CalcTangentSpace
	);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Can't load scene for " << filename << std::endl;
		std::cerr << importer.GetErrorString() << std::endl;
		exit(1);
	}

	_root = this->process_node(scene->mRootNode, scene);
}

template<typename NODE_DEFINITION>
std::unique_ptr<NODE_DEFINITION> LoadedModel<NODE_DEFINITION>::process_node(const aiNode* node, const aiScene* scene) const
{
	ModelNodeDefinition::meshes_vector meshes;
	meshes.reserve(node->mNumMeshes);
	for (unsigned int mesh_i = 0; mesh_i < node->mNumMeshes; mesh_i++) {
		unsigned int global_index = node->mMeshes[mesh_i];
		const aiMesh* mesh = scene->mMeshes[global_index];
		meshes.push_back(std::make_unique<MeshModel>(mesh));
	}

	ModelNodeDefinition::children_vector children;
	children.reserve(node->mNumChildren);
	for (unsigned int child_i = 0; child_i < node->mNumChildren; child_i++) {
		const aiNode* childnode = node->mChildren[child_i];
		std::unique_ptr<NODE_DEFINITION> childmodel = this->process_node(childnode, scene);
		children.push_back(std::move(childmodel));
	}

	return std::make_unique<NODE_DEFINITION>(std::move(meshes), std::move(children), node->mTransformation);
}

template<typename NODE_DEFINITION>
void LoadedModel<NODE_DEFINITION>::render(GLuint program)
{
	if (_use_internode_location == -2) {
		_use_internode_location = glGetUniformLocation(program, "use_modelintern");
		if (_use_internode_location == -1) {
			std::cerr << "use_modelintern uniform is not present" << std::endl;
		}
	}

	glUseProgram(program);
	glUniform1i(_use_internode_location, GL_TRUE);
	this->_root->render(program);
	glUniform1i(_use_internode_location, GL_FALSE);
}

#endif