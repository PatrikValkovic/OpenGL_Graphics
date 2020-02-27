#include "ShadersSupport.h"
#include <fstream>


GLuint compile_shader(std::string filepath, GLuint shader_type) {
	using namespace std;
	
	char* shader_code = nullptr;
	{
		ifstream f(filepath, ifstream::in);
		f.seekg(0, ifstream::end);
		unsigned int length = f.tellg();
		f.seekg(0, ifstream::beg);
		shader_code = new char[length + 1];
		f.read(shader_code, length);
	}
	
	GLuint shader;
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_code, nullptr);
	glCompileShader(shader);

	delete[] shader_code;
	return shader;
}