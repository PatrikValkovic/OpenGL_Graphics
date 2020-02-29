#version 440 core

in vec3 finalColor;

out vec4 color;

void main() {
	color = vec4(finalColor, 1);
}