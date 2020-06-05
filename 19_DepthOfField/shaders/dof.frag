#version 440 core

in vec2 TextureCoords;
out vec4 color;

uniform sampler2D screenTexture;
uniform float opacity;


void main() {
	color = vec4(vec3(texture(screenTexture, TextureCoords)), opacity);
}