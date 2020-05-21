#ifndef __TEXTURE_TYPES_H__
#define __TEXTURE_TYPES_H__
#include <map>
#include <set>

enum class TextureTypes : unsigned int {
	diffuse = 0x1,
	specular = 0x2,
	specular_light = 0x4,
	ambient_occlusion = 0x8,
	normal = 0x10,
	rougness = 0x20,
	all = 0xFF,
};

const std::map<TextureTypes, const char*> TEXTURETYPE_TO_UNIFORM = {
	std::make_pair(TextureTypes::diffuse, "diffuse_texture"),
	std::make_pair(TextureTypes::specular, "specular_texture"),
	std::make_pair(TextureTypes::specular_light, "specular_light_texture"),
	std::make_pair(TextureTypes::ambient_occlusion, "ambient_occlusion_texture"),
	std::make_pair(TextureTypes::normal, "normal_texture"),
	std::make_pair(TextureTypes::rougness, "roughness_texture"),
};
const std::map<TextureTypes, const char*> TEXTURETYPE_TO_COORD = {
	std::make_pair(TextureTypes::diffuse, "diffuse_coord"),
	std::make_pair(TextureTypes::specular, "specular_coord"),
	std::make_pair(TextureTypes::specular_light, "specular_light_coord"),
	std::make_pair(TextureTypes::ambient_occlusion, "ambient_occlusion_coord"),
	std::make_pair(TextureTypes::normal, "normal_coord"),
	std::make_pair(TextureTypes::rougness, "roughness_coord"),
};

#endif