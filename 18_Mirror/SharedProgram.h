#ifndef __PROGRAM_SHARED_H__
#define __PROGRAM_SHARED_H__
#include <glm.hpp>

#define vec4 glm::vec4
#define vec3 glm::vec3
#define vec2 glm::vec2
#define uint GLuint
#define float GLfloat
#define int GLint

#include "Constants.h"
#include "LightDefinition.h"
#include "MaterialDefinition.h"

#undef vec4
#undef vec3
#undef vec2
#undef uint
#undef float
#undef int

#endif