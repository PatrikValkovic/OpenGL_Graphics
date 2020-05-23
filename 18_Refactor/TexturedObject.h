#ifndef __TEXTURED_OBJECT_H__
#define __TEXTURED_OBJECT_H__
#include <vector>
#include "RenderableObject.h"
#include "Texture.h"
#include "TextureTypes.h"


class TexturedObject: public RenderableObject
{
protected:
	struct Wrap {
		Wrap(Texture&& texture, TextureTypes type);
		Wrap(Wrap&&) = default;
		Texture texture;
		TextureTypes type;
		GLint sampler_location;
		GLint pos_location;
		int coord_index;
	};
	std::vector<Wrap> _textures;
public:
	TexturedObject(
		Renderable& renderable,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::vec3 rotate = glm::vec3(0.0f)
	);

	TexturedObject& useTexture(const char* texturefile, TextureTypes type, unsigned int coords_index, bool flip_texture = true);
	TexturedObject& useTexture(Texture &&texture, TextureTypes type, unsigned int coords_index);

	virtual void render(GLuint program, glm::mat4 model, glm::mat4* view = nullptr, glm::mat4* projection = nullptr) override;
	virtual void render(GLuint program) override;
};

#endif