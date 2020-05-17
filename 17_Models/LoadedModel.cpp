#include "LoadedModel.h"
#include <vector>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm.hpp>


LoadedModel::LoadedModel(const char* filename, GLuint program)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		filename,
		aiPostProcessSteps::aiProcess_Triangulate | 
		aiPostProcessSteps::aiProcess_FlipUVs
	);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Can't load scene for " << filename << std::endl;
		std::cerr << importer.GetErrorString() << std::endl;
		exit(1);
	}

	int current_indice_index = 0;
	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];

		for (int vertex_i = 0; vertex_i < mesh->mNumVertices; vertex_i++) {
			Vertex v;
			v.position = glm::vec3(
				mesh->mVertices[vertex_i].x,
				mesh->mVertices[vertex_i].y,
				mesh->mVertices[vertex_i].z
			);
			_vertices.push_back(v);
		}

		for (int face_i = 0; face_i < mesh->mNumFaces; face_i++) {
			aiFace& face = mesh->mFaces[face_i];
			for (int j = 0; j < face.mNumIndices; j++) {
				_indices.push_back(face.mIndices[j] + current_indice_index);
			}
		}

		current_indice_index += mesh->mNumVertices;
	}

	glUseProgram(program);
	glGenBuffers(1, &_vertexBuffer);
	glGenVertexArrays(1, &_vertexArray);
	glGenBuffers(1, &_indexBuffer);
	
	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _indices.size(), _indices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return;
}

void LoadedModel::render(GLuint program) const
{
	this->_render(
		program,
		[this]() {
			glBindVertexArray(_vertexArray);
			glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	);
}