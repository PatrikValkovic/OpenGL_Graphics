#include "Texture.h"

#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "SDLsupport.h"

Texture::Texture(RAIIArray<>&& texture)
	: _texture(std::move(texture))
{}

Texture Texture::fromSurface(SDL_Surface* surf, GLenum wrap_s, GLenum wrap_t, GLenum min_filter, GLenum mag_filter)
{
	// create texture
	RAIIArray<> texture(glDeleteTextures, glGenTextures);
	// flip image
	std::vector<char> flipped_data(surf->h * surf->pitch);
	for (int r = 0; r < surf->h; r++) {
		memcpy(
			flipped_data.data() + (surf->h - r - 1) * surf->pitch,
			static_cast<char*>(surf->pixels) + r * surf->pitch,
			surf->pitch
			);
	}
	// fill texture
	bool is_rgba = surf->format->Amask != 0;
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D( // generates the texture
		GL_TEXTURE_2D, // texture target
		0, //mipmap level
		is_rgba ? GL_RGBA : GL_RGB, // format in which we want to STORE texture
		surf->w, // texture width
		surf->h, // texture height
		0, //always 0, some legacy shit
		is_rgba ? GL_RGBA : GL_RGB, // format of the SOURCE picture
		GL_UNSIGNED_BYTE, // datatype of the SOURCE image
		flipped_data.data() // data
		);
	//glGenerateMipmap(GL_TEXTURE_2D); // use mitmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s); //repeat texture over x axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t); // clamp texture over y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter); // use nearest algorithm when minimazing
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter); // use linear algorithm when magnifying the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	std::cout << "Texture from surface loaded" << std::endl;
	return Texture(std::move(texture));
}

Texture Texture::fromFile(std::string filepath, GLenum wrap_s, GLenum wrap_t, GLenum min_filter, GLenum mag_filter)
{
	RAII<SDL_Surface*> imgSurface(SDL_FreeSurface, IMG_Load, filepath.c_str());
	if (!imgSurface) {
		std::cerr << IMG_GetError() << std::endl;
		throw LoadException((std::string("Can't load image ") + filepath).c_str());
	}
	Texture t = Texture::fromSurface(imgSurface, wrap_s, wrap_t, min_filter, mag_filter);
	std::cout << "Texture from file " << filepath << " loaded" << std::endl;
	return std::move(t);
}
