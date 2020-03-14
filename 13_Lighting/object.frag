#version 440 core

in vec3 Normal;
in vec3 FragmentPosition;

out vec4 color;

uniform float ambient_strength;
uniform vec3 ambient_color;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform float light_strength;
uniform float ligh_specular_strength;
uniform vec3 camera_view_direction;
uniform unsigned int ligh_reflectness;



void main() {

	vec4 objectColor = vec4(1.0f, 0.5f, 0.31f, 1.0f);

	// ambient light
	vec3 ambient = ambient_color * ambient_strength;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(light_pos - FragmentPosition);
	float diffuseStrength = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = diffuseStrength * light_color * light_strength;

	// specular
	vec3 viewDir = normalize(camera_view_direction);
	vec3 reflectDir = reflect(-lightDirection, norm);
	float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
	float spec = pow(viewReflectAngle, ligh_reflectness);
	vec3 specular = ligh_specular_strength * spec * light_color;


	color = vec4((ambient + diffuse + specular) * vec3(objectColor), objectColor.w);
}