#include "MeshModel.h"
#include <iostream>
#include <vector>
#include "SharedProgram.h"

using namespace std;

MeshModel::MeshModel(const aiMesh* mesh) : ElementBufferModel()
{
	vector<VertexDefinition> vertices;
	vector<unsigned int> indices;

	if (!mesh->mColors[0]) {
		cerr << "Model doesn't has colors defined" << endl;
	}

	for (unsigned int vertex_i = 0; vertex_i < mesh->mNumVertices; vertex_i++) {
		VertexDefinition vertex;
		vertex.position = glm::vec3(
			mesh->mVertices[vertex_i].x,
			mesh->mVertices[vertex_i].y,
			mesh->mVertices[vertex_i].z
		);
		vertex.normal = glm::vec3(
			mesh->mNormals[vertex_i].x,
			mesh->mNormals[vertex_i].y,
			mesh->mNormals[vertex_i].z
		);
		if (mesh->mColors[0] != nullptr) {
			vertex.color = glm::vec4(
				mesh->mColors[0][vertex_i].r,
				mesh->mColors[0][vertex_i].g,
				mesh->mColors[0][vertex_i].b,
				mesh->mColors[0][vertex_i].a
			);
		}
		for (unsigned int text_i = 0; text_i < VertexDefinition::MAX_TEXTURES && mesh->mTextureCoords[text_i] != nullptr; text_i++) {
			vertex.textureCoords[text_i] = glm::vec2(
				mesh->mTextureCoords[text_i][vertex_i].x,
				mesh->mTextureCoords[text_i][vertex_i].y
			);
		}
		vertices.push_back(vertex);
	}

	for (unsigned int face_i = 0; face_i < mesh->mNumFaces; face_i++) {
		aiFace& face = mesh->mFaces[face_i];
		for (unsigned int i = 0; i < face.mNumIndices; i++)
			indices.push_back(face.mIndices[i]);
		//indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
	}
	_numOfElements = static_cast<unsigned int>(indices.size());

	// bind
	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	// fill data
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDefinition) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	// bind attribs
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexDefinition), reinterpret_cast<void*>(offsetof(VertexDefinition, position)));
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(VertexDefinition), reinterpret_cast<void*>(offsetof(VertexDefinition, normal)));
	glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(VertexDefinition), reinterpret_cast<void*>(offsetof(VertexDefinition, color)));
	for(int i=3; i < 3 + MAX_TEXTURES; i++)
		glVertexAttribPointer(3, 2, GL_FLOAT, false, sizeof(VertexDefinition), reinterpret_cast<void*>(offsetof(VertexDefinition, textureCoords[i])));
	for (unsigned int i = 0; i < 3 + MAX_TEXTURES; i++)
		glEnableVertexAttribArray(i);
	// unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshModel::render(GLuint program)
{
	this->_render(
		program,
		[this]() {
			glDrawElements(GL_TRIANGLES, _numOfElements, GL_UNSIGNED_INT, nullptr);
		}
	);
	return;
}
