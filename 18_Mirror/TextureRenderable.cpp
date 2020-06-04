#include "TextureRenderable.h"

UniformWrapper TextureRenderable::_uniform;

TextureRenderable::TextureRenderable(Renderable* inner, GLuint texture, TextureSlots slot, std::string uniform_variable)
	: WrapRenderable(inner), _texture(texture), _slot(slot), _variable(uniform_variable)
{}

void TextureRenderable::render(GLuint program)
{
	GLint texture_position = _uniform.uniformloc(program, _variable);
	glActiveTexture(static_cast<GLuint>(_slot));
	glBindTexture(GL_TEXTURE_2D, _texture);
	glUniform1i(texture_position, static_cast<GLuint>(_slot) - GL_TEXTURE0);

	WrapRenderable::render(program);
}