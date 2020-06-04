#ifndef __VERTEX_DEFINITION_H__
#define __VERTEX_DEFINITION_H__

#include <glm.hpp>
#include "Constants.h"

struct VertexDefinition {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec4 color;
	glm::vec2 textureCoords[MAX_TEXTURES];
};

#endif
