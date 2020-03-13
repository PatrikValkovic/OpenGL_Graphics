#include "ShadersSupport.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <memory>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
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
		char* info_log = new char[std::max(length, 1)];
		glGetProgramInfoLog(program, length, nullptr, info_log);
		info_log[length] = 0;
		cerr << info_log << endl;
		delete[] info_log;
		throw LoadException("Coudn't link program");
	}
	else {
		cout << "Program " << program << " linked successfully" << endl;
	}
}

RAIIArray<> load_texture(std::string filepath, GLenum overS, GLenum overT)
{
	RAIIArray<> texture(glDeleteTextures, glGenTextures);
	RAII<SDL_Surface*> imgSurface(SDL_FreeSurface, IMG_Load, filepath.c_str());
	if (!imgSurface) {
		std::cerr << IMG_GetError() << std::endl;
		throw LoadException("Can't load image wall.jpg");
	}
	bool is_rgba = imgSurface->format->Amask != 0;
	glBindTexture(GL_TEXTURE_2D, texture);
	glad_glTexImage2D( // generates the texture
		GL_TEXTURE_2D, // texture target
		0, //mipmap level
		is_rgba ? GL_RGBA : GL_RGB, // format in which we want to STORE texture
		imgSurface->w, // texture width
		imgSurface->h, // texture height
		0, //always 0, some legacy shit
		is_rgba ? GL_RGBA : GL_RGB, // format of the SOURCE picture
		GL_UNSIGNED_BYTE, // datatype of the SOURCE image
		imgSurface->pixels // data
	);
	//glGenerateMipmap(GL_TEXTURE_2D); // use mitmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, overS); //repeat texture over x axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, overT); // clamp texture over y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // use nearest algorithm when minimazing
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // use linear algorithm when magnifying the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	std::cout << "Texture " << filepath << " loaded" << std::endl;
	return texture;
}
