#ifndef __LOADED_MODEL_H__
#define __LOADED_MODEL_H__
#include <iostream>
#include <vector>
#include <memory>
#include <glad/glad.h>
#include "MeshModel.h"
#include "ComposeObject.h"

class ModelObject: public ComposeObjectDestroy
{
private:
	ComposeObjectDestroy* process_node(const aiNode* node, const aiScene* scene) const;
public:
	ModelObject(const char* filename);
};







#endif