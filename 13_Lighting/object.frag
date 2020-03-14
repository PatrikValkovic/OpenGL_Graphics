#version 440 core

in vec3 Normal;
in vec3 FragmentPosition;

out vec4 color;

uniform float ambient_strength;
uniform vec3 ambient_color;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform float light_strength;



void main() {

	vec4 objectColor = vec4(1.0f, 0.5f, 0.31f, 1.0f);

	// ambient light
	vec3 ambient = ambient_color * ambient_strength;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(light_pos - FragmentPosition);
	float diffuseStrength = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = diffuseStrength * light_color * light_strength;

	color = vec4((ambient + diffuse) * vec3(objectColor), objectColor.w);
}