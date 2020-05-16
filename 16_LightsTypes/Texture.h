#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>
#include <SDL.h>
#include <glad/glad.h>
#include "RAII.h"

class Texture
{
protected:
	RAIIArray<> _texture;
	Texture(RAIIArray<> &&texture);
public:
	Texture(const Texture&) = delete;
	Texture(Texture&&) = default;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = default;
	virtual ~Texture() = default;

	static Texture fromSurface(
		SDL_Surface* surf,
		GLenum wrap_s = GL_REPEAT,
		GLenum wrap_t = GL_REPEAT,
		GLenum min_filter = GL_NEAREST,
		GLenum mag_filter = GL_LINEAR
	);

	static Texture fromFile(
		std::string filepath,
		GLenum wrap_s = GL_REPEAT,
		GLenum wrap_t = GL_REPEAT,
		GLenum min_filter = GL_NEAREST,
		GLenum mag_filter = GL_LINEAR
	);

	inline GLuint getTexture() const noexcept {
		return _texture;
	}
	inline operator GLuint() const noexcept {
		return getTexture();
	}
};

#endif