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

	color = Color;
}