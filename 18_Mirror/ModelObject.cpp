#include "ModelObject.h"
#include <gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>


ModelObject::ModelObject(const char* filename)
	: ComposeObjectDestroy()
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

	//TODO load texture
	if (false) {
		unsigned int numMaterials = scene->mNumMaterials;
		std::cout << "MATERIALS: " << numMaterials << std::endl;
		for (unsigned int material_i=0; material_i < numMaterials; material_i++) {
			aiMaterial* mat = scene->mMaterials[material_i];
			for (unsigned int prop_i = 0; prop_i < mat->mNumProperties; prop_i++) {
				aiMaterialProperty* prop = mat->mProperties[prop_i];
				char* data = new char[prop->mDataLength+1];
				std::memcpy(data, prop->mData, prop->mDataLength);
				data[prop->mDataLength] = '\0';
				std::cout << "Prop " << prop->mKey.C_Str() << "=" << data << std::endl;
				delete[] data;
			}
			std::cout << std::endl;
			unsigned int textures = mat->GetTextureCount(aiTextureType_DIFFUSE);
			std::cout << "TEXTURES: " << textures << std::endl;
			if (textures > 0) {
				aiString path;
				mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
				std::cout << "TEXTURE: " << path.C_Str() << std::endl;
			}
		}
	}

	this->addObject(this->process_node(scene->mRootNode, scene));
}

ComposeObjectDestroy* ModelObject::process_node(const aiNode* node, const aiScene* scene) const
{
	ComposeObjectDestroy* current_node = new ComposeObjectDestroy();

	const aiMatrix4x4 &t = node->mTransformation;
	current_node->setFromMatrix(
		glm::mat4(
			t.a1, t.b1, t.c1, t.d1,
			t.a2, t.b2, t.c2, t.d2,
			t.a3, t.b3, t.c3, t.d3,
			t.a4, t.b4, t.c4, t.d4
		)
	);

	for (unsigned int mesh_i = 0; mesh_i < node->mNumMeshes; mesh_i++) {
		unsigned int global_index = node->mMeshes[mesh_i];
		const aiMesh* mesh = scene->mMeshes[global_index];
		current_node->addObject(new RenderableObjectDestroy(new MeshModel(mesh)));
	}

	for (unsigned int child_i = 0; child_i < node->mNumChildren; child_i++) {
		const aiNode* childnode = node->mChildren[child_i];
		ComposeObjectDestroy* childobject = this->process_node(childnode, scene);
		current_node->addObject(childobject);
	}

	return current_node;
}
