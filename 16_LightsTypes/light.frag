#version 440 core

struct SpotLight {
	vec3 position;
	vec3 color;
	float distanceCoeficient;
	float strength;
};

uniform SpotLight light;

out vec4 color;


void main() {

	color = vec4(light.color, 1.0f);
}