#include "TexturedObject.h"

UniformWrapper TexturedObject::_uniform;


TexturedObject::TexturedObject(RenderableObject* renderable, glm::vec3 translate, glm::vec3 scale, glm::mat3 rotate)
	: WrapObject(renderable, translate, scale, rotate)
{}


TexturedObject& TexturedObject::useTexture(const char* texturefile, TextureTypes type, unsigned int coords_index, bool flip_texture)
{
	return this->useTexture(Texture::fromFile(texturefile, flip_texture), type, coords_index);
}

TexturedObject& TexturedObject::useTexture(Texture&& texture, TextureTypes type, unsigned int coords_index)
{
	auto ptr = std::make_unique<WrapIncludingTexture>(std::move(texture));
	ptr->texture = ptr->texture_instance;
	ptr->type = type;
	ptr->coord_index = coords_index;
	_textures.push_back(std::move(ptr));

	return *this;
}

TexturedObject& TexturedObject::useTexture(GLuint texture, TextureTypes type, unsigned int coords_index)
{
	auto ptr = std::make_unique<Wrap>();
	ptr->texture = texture;
	ptr->type = type;
	ptr->coord_index = coords_index;
	_textures.push_back(std::move(ptr));

	return *this;
}


void TexturedObject::render(GLuint program, glm::mat4 model)
{
	glUseProgram(program);

	std::set<TextureTypes> not_used;
	for (auto entry : TEXTURETYPE_TO_COORD)
		not_used.insert(entry.first);

	for (unsigned int i = 0; i < _textures.size(); i++) {
		std::unique_ptr<Wrap> &w = _textures[i];
		GLuint slot = static_cast<GLuint>(TextureSlots::Texture31) - i;
		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, w->texture);
		glUniform1i(_uniform(program, TEXTURETYPE_TO_UNIFORM.at(w->type)), slot - GL_TEXTURE0);
		glUniform1i(_uniform(program, TEXTURETYPE_TO_COORD.at(w->type)), w->coord_index);
		not_used.erase(w->type);
	}

	for (TextureTypes type : not_used) {
		const char* name = TEXTURETYPE_TO_COORD.at(type);
		GLint position = _uniform(program, name);
		glUniform1i(position, -1);
	}

	return WrapObject::render(program, model);
}

void TexturedObject::render(GLuint program)
{
	return WrapObject::render(program);
}






TexturedObject::WrapIncludingTexture::WrapIncludingTexture(Texture&& texture)
	: texture_instance(std::move(texture))
{}