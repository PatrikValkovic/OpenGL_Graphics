#include "TextureRenderable.h"
#include <iostream>

TextureRenderable::TextureRenderable(Renderable& inner, GLuint texture, TextureSlots slot, std::string uniform_variable)
	: WrapRenderable(inner), _texture(texture), _slot(slot), _variable(uniform_variable)
{}

void TextureRenderable::render(GLuint program)
{
	glUseProgram(program);

	GLint texture_position = glGetUniformLocation(program, _variable.c_str());
	if (texture_position == -1) {
		std::cerr << _variable << " uniform variable not found" << std::endl;
	}
	glActiveTexture(static_cast<GLuint>(_slot));
	glBindTexture(GL_TEXTURE_2D, _texture);
	glUniform1i(texture_position, static_cast<GLuint>(_slot) - GL_TEXTURE0);

	_inner.render(program);
}
