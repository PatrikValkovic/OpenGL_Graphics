#include "ShadersSupport.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <memory>
#include "SDLsupport.h"


GLuint compile_shader(std::string filepath, GLuint shader_type) {
	using namespace std;
	
	char* shader_code = nullptr;
	{
		ifstream f(filepath, ifstream::in | ios::binary);
		if (!f) {
			throw LoadException((string("Can't open file ") + filepath).c_str());
		}
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
		GLint log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		char* info_log = new char[log_length];
		glGetShaderInfoLog(shader, log_length, nullptr, info_log);
		cerr << info_log << endl;
		delete[] info_log;
		throw LoadException((string("Compilation of shader ") + filepath + " unsuccessfull").c_str());
	}
	if (status == GL_TRUE) {
		cout << "Compilation of shader " << filepath << " successfull" << endl;
	}
	 
	delete[] shader_code;
	return shader;
}

void link_program(GLuint program)
{
	using namespace std;
	glLinkProgram(program);
	GLint status = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* info_log = new char[length];
		glGetProgramInfoLog(program, length, nullptr, info_log);
		cerr << info_log << endl;
		delete[] info_log;
		throw LoadException("Coudn't link program");
	}
	else {
		cout << "Program " << program << " linked successfully" << endl;
	}
}
