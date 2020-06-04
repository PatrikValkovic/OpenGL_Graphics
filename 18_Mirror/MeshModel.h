#ifndef __MESH_MODEL_H__
#define __MESH_MODEL_H__
#include <assimp/scene.h>
#include "ElementBufferModel.h"
#include "VertexDefinition.h"

class MeshModel : public ElementBufferModel
{
public:
	MeshModel(const aiMesh* mesh);
	MeshModel(const MeshModel&) = delete;
	MeshModel(MeshModel&&) = default;
	MeshModel& operator=(const MeshModel&) = delete;
	MeshModel& operator=(MeshModel&&) = default;
	virtual ~MeshModel() = default;

	virtual void render(GLuint program) override;
};

#endif