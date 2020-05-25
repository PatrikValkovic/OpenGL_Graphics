#ifndef __TEXTURED_OBJECT_H__
#define __TEXTURED_OBJECT_H__
#include <vector>
#include <iostream>
#include "WrapObject.h"
#include "Texture.h"
#include "TextureTypes.h"
#include "TextureSlots.h"
#include "UniformWrapper.h"

class TexturedObject: public WrapObject
{
protected:
	static UniformWrapper _uniform;
	class Wrap {
	public:
		Wrap() = default;
		Wrap(Wrap&&) = default;
		GLuint texture;
		TextureTypes type;
		int coord_index = -1;
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
		RenderableObject* renderable,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::mat3 rotate = glm::mat3(1.0f)
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







#endif

