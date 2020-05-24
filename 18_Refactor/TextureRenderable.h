#ifndef __TEXTURE_RENDERABLE_H__
#define __TEXTURE_RENDERABLE_H__

#include <string>
#include <glad/glad.h>
#include "WrapRenderable.h"
#include "Texture.h"
#include "TextureSlots.h"
#include "UniformWrapper.h"

template<typename PTRTYPE>
class TextureRenderable : public WrapRenderable<PTRTYPE>
{
private:
	GLuint _texture;
	TextureSlots _slot;
	const std::string _variable;
	UniformWrapper _uniform;
public:
	TextureRenderable(PTRTYPE&& inner, GLuint texture, TextureSlots slot, std::string uniform_variable);

	virtual void render(GLuint program) override;

};


using TextureRenderableRef = TextureRenderable<Renderable&>;
using TextureRenderablePtr = TextureRenderable<Renderable*>;
using TextureRenderableUniq = TextureRenderable<std::unique_ptr<Renderable>>;
using TextureRenderableShare = TextureRenderable<std::shared_ptr<Renderable>>;


template<typename PTRTYPE>
TextureRenderable<PTRTYPE>::TextureRenderable(PTRTYPE&& inner, GLuint texture, TextureSlots slot, std::string uniform_variable)
	: WrapRenderable<PTRTYPE>(std::move(inner)), _texture(texture), _slot(slot), _variable(uniform_variable), _uniform()
{}
template<>
TextureRenderable<Renderable&>::TextureRenderable(Renderable& inner, GLuint texture, TextureSlots slot, std::string uniform_variable)
	: WrapRenderable<Renderable&>(inner), _texture(texture), _slot(slot), _variable(uniform_variable), _uniform()
{}

template<typename PTRTYPE>
void TextureRenderable<PTRTYPE>::render(GLuint program)
{
	GLint texture_position = _uniform.uniformloc(program, _variable);
	glActiveTexture(static_cast<GLuint>(_slot));
	glBindTexture(GL_TEXTURE_2D, _texture);
	glUniform1i(texture_position, static_cast<GLuint>(_slot) - GL_TEXTURE0);

	WrapRenderable<PTRTYPE>::render(program);
}


#endif