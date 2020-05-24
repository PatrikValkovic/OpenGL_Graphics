#ifndef __TEXTURED_OBJECT_H__
#define __TEXTURED_OBJECT_H__
#include <vector>
#include <iostream>
#include "RenderableObject.h"
#include "Texture.h"
#include "TextureTypes.h"
#include "TextureSlots.h"
#include "UniformWrapper.h"

template<typename PTRTYPE = Renderable>
class TexturedObject: public RenderableObject<PTRTYPE>
{
protected:
	static UniformWrapper _uniform;
	class Wrap {
	public:
		Wrap() = default;
		Wrap(Wrap&&) = default;
		GLuint texture;
		TextureTypes type;
		GLint sampler_location;
		GLint pos_location;
		int coord_index;
	};
	class WrapIncludingTexture : public Wrap {
	public:
		WrapIncludingTexture(Texture&& texture);
		WrapIncludingTexture(WrapIncludingTexture&&) = default;
		Texture texture_instance;
	};
	std::vector<std::unique_ptr<Wrap>> _textures;
public:
	TexturedObject(
		PTRTYPE&& renderable,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotate = glm::vec3(0.0f)
	);
	TexturedObject(const TexturedObject&) = delete;
	TexturedObject(TexturedObject&&) = default;	
	TexturedObject& operator=(const TexturedObject&) = delete;
	TexturedObject& operator=(TexturedObject&&) = default;
	virtual ~TexturedObject() = default;

	TexturedObject& useTexture(const char* texturefile, TextureTypes type, unsigned int coords_index, bool flip_texture = true);
	TexturedObject& useTexture(Texture&& texture, TextureTypes type, unsigned int coords_index);
	TexturedObject& useTexture(GLuint texture, TextureTypes type, unsigned int coords_index);

	virtual void render(GLuint program, glm::mat4 model) override;
	virtual void render(GLuint program) override;
};

using TexturedObjectRef = TexturedObject<Renderable&>;
using TexturedObjectPtr = TexturedObject<Renderable*>;
using TexturedObjectUniq = TexturedObject<std::unique_ptr<Renderable>>;
using TexturedObjectShare = TexturedObject<std::shared_ptr<Renderable>>;


template<typename PTRTYPE>
TexturedObject<PTRTYPE>::TexturedObject(PTRTYPE &&renderable, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: RenderableObject<PTRTYPE>(renderable, translate, scale, rotate)
{}

template<typename PTRTYPE>
TexturedObject<PTRTYPE>& TexturedObject<PTRTYPE>::useTexture(const char* texturefile, TextureTypes type, unsigned int coords_index, bool flip_texture)
{
	return this->useTexture(Texture::fromFile(texturefile, flip_texture), type, coords_index);
}

template<typename PTRTYPE>
TexturedObject<PTRTYPE>& TexturedObject<PTRTYPE>::useTexture(Texture&& texture, TextureTypes type, unsigned int coords_index)
{
	auto ptr = std::make_unique<WrapIncludingTexture>(std::move(texture));
	ptr->texture = ptr->texture_instance;
	ptr->type = type;
	ptr->coord_index = coords_index;
	_textures.push_back(std::move(ptr));

	return *this;
}

template<typename PTRTYPE>
TexturedObject<PTRTYPE>& TexturedObject<PTRTYPE>::useTexture(GLuint texture, TextureTypes type, unsigned int coords_index)
{
	auto ptr = std::make_unique<Wrap>();
	ptr->texture = texture;
	ptr->type = type;
	ptr->coord_index = coords_index;
	_textures.push_back(std::move(ptr));

	return *this;
}


template<typename PTRTYPE>
void TexturedObject<PTRTYPE>::render(GLuint program, glm::mat4 model)
{
	glUseProgram(program);

	std::set<TextureTypes> not_used;
	for (auto entry : TEXTURETYPE_TO_COORD)
		not_used.insert(entry.first);

	for (unsigned int i = 0; i < _textures.size(); i++) {
		std::unique_ptr<Wrap> w = _textures[i];
		if (w->sampler_location == -2 || w->pos_location == -2) {
			const char* sampler_name = TEXTURETYPE_TO_UNIFORM.at(w->type);
			const char* location_name = TEXTURETYPE_TO_COORD.at(w->type);
			w->sampler_location = _uniform(program, sampler_name);
			w->pos_location = _uniform(program, location_name);
		}

		GLuint slot = static_cast<GLuint>(TextureSlots::Texture31) - i;
		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, w->texture);
		glUniform1i(w->sampler_location, slot - GL_TEXTURE0);
		glUniform1i(w->pos_location, w->coord_index);
		not_used.erase(w->type);
	}

	for (TextureTypes type : not_used) {
		const char* name = TEXTURETYPE_TO_COORD.at(type);
		int position = glGetUniformLocation(program, name);
		glUniform1i(position, -1);
	}

	return RenderableObject::render(program, model);
}

template<typename PTRTYPE>
void TexturedObject<PTRTYPE>::render(GLuint program)
{
	return RenderableObject::render(program);
}






template<typename PTRTYPE>
inline TexturedObject<PTRTYPE>::WrapIncludingTexture::WrapIncludingTexture(Texture&& texture)
	: texture_instance(std::move(texture))
{}



#endif

