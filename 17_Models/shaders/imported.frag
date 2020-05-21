#version 440 core

in vec3 Normal;
in vec4 Color;
in vec3 Position;
in vec2 TextureCoords[4];

out vec4 color;

uniform sampler2D diffuse_texture;
uniform uint diffuse_coord;
uniform sampler2D specular_texture;
uniform uint specular_coord;
uniform sampler2D specular_light_texture;
uniform uint specular_light_coord;
uniform sampler2D ambient_occlusion_texture;
uniform uint ambient_occlusion_coord;
uniform sampler2D normal_texture;
uniform uint normal_coord;
uniform sampler2D roughness_texture;
uniform uint roughness_coord;

void main() {

	//vec2 texture_coords = TextureCoords[diffuse_coord];
	//vec3 objectColor = vec3(texture(diffuse_texture, vec2(0.66f, 0.66f)));

	color = Color;

	if(diffuse_coord >= 0){
		vec3 objectColor = vec3(texture(diffuse_texture, vec2(-1.0, -1.0) + TextureCoords[diffuse_coord]));
		color = vec4(objectColor, 1);
	}

}