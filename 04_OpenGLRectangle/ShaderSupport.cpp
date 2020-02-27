#include "ShadersSupport.h"
#include <fstream>
#include <iostream>
#include <cstring>


GLuint compile_shader(std::string filepath, GLuint shader_type) {
	using namespace std;
	
	char* shader_code = nullptr;
	{
		ifstream f(filepath, ifstream::in | ios::binary);
		f.seekg(0, ifstream::end);
		std::streamoff length = f.tellg();
		f.seekg(0, ifstream::beg);
		shader_code = new char[length + 1];
		f.read(shader_code, length);
		shader_code[length] = 0;
	}
	
	GLuint shader;
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_code, nullptr);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		std::cout << "Compilation unsuccessfull" << std::endl;
		//TODO handle
	}
	 
	delete[] shader_code;
	return shader;
}