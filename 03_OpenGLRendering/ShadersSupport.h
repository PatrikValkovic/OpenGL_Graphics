#ifndef __SHADERS_SUPPORT_H__
#define __SHADERS_SUPPORT_H__

#include <string>
#include <glad.h>

GLuint compile_shader(std::string filepath, GLuint shader_type);

#endif