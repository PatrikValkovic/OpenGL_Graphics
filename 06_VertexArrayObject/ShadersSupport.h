#ifndef __SHADERS_SUPPORT_H__
#define __SHADERS_SUPPORT_H__

#include <string>
#include <glad/glad.h>

GLuint compile_shader(std::string filepath, GLuint shader_type);

void link_program(GLuint program);

#endif