#include "TexturedObject.h"
#include <iostream>
#include "TextureSlots.h"

TexturedObject::TexturedObject(Renderable& renderable, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: RenderableObject(renderable, translate, scale, rotate)
{}

TexturedObject& TexturedObject::useTexture(const char* texturefile, TextureTypes type, unsigned int coords_index, bool flip_texture)
{
	return this->useTexture(Texture::fromFile(texturefile, flip_texture), type, coords_index);
}

TexturedObject& TexturedObject::useTexture(Texture&& texture, TextureTypes type, unsigned int coords_index)
{
	Wrap wrapper(std::move(texture), type);
	wrapper.coord_index = coords_index;
	_textures.push_back(std::move(wrapper));

	return *this;
}

void TexturedObject::render(GLuint program, glm::mat4 model, glm::mat4* view, glm::mat4* projection)
{
	glUseProgram(program);

	std::set<TextureTypes> not_used;
	for (auto entry : TEXTURETYPE_TO_COORD)
		not_used.insert(entry.first);

	for(unsigned int i=0;i < _textures.size(); i++){
		Wrap& w = _textures[i];
		if (w.sampler_location == -2 || w.pos_location == -2) {
			const char* sampler_name = TEXTURETYPE_TO_UNIFORM.at(w.type);
			const char* location_name = TEXTURETYPE_TO_COORD.at(w.type);
			w.sampler_location = glGetUniformLocation(program, sampler_name);
			if (w.sampler_location < 0) {
				std::cerr << sampler_name << " uniform variable doesn't exists" << std::endl;
			}
			w.pos_location = glGetUniformLocation(program, location_name);
			if (w.pos_location < 0) {
				std::cerr << location_name << " uniform variable doesn't exists" << std::endl;
			}
		}

		GLuint slot = static_cast<GLuint>(TextureSlots::Texture31) - i;
		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, w.texture);
		glUniform1i(w.sampler_location, slot - GL_TEXTURE0);
		glUniform1i(w.pos_location, w.coord_index);
		not_used.erase(w.type);
	}

	for (TextureTypes type : not_used) {
		const char* name = TEXTURETYPE_TO_COORD.at(type);
		int position = glGetUniformLocation(program, name);
		glUniform1i(position, -1);
	}

	return RenderableObject::render(program, model, view, projection);
}

void TexturedObject::render(GLuint program)
{
	return RenderableObject::render(program);
}





TexturedObject::Wrap::Wrap(Texture&& texture, TextureTypes type)
	: texture(std::move(texture)), type(type), sampler_location(-2), pos_location(-2), coord_index(-1)
{}
