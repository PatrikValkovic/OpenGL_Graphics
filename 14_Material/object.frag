#version 440 core

struct SpotLight {
	vec3 position;
	vec3 color;
	float distanceCoeficient;
	float strength;
};

in vec3 Normal;
in vec3 FragmentPosition;

out vec4 color;

uniform float ambient_strength;
uniform vec3 ambient_color;

uniform SpotLight light;
uniform vec3 camera_view_direction;



void main() {

	vec4 objectColor = vec4(1.0f, 0.5f, 0.31f, 1.0f);

	// ambient light
	vec3 ambient = ambient_color * ambient_strength;

	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(light.position - FragmentPosition);
	float diffuseStrength = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = diffuseStrength * light.color * light.strength;

	
	// specular
	vec3 viewDir = normalize(camera_view_direction);
	vec3 reflectDir = reflect(-lightDirection, norm);
	float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
	float spec = pow(viewReflectAngle, 32);
	vec3 specular = light.strength * spec * light.color;
	

	color = vec4((ambient + diffuse + specular) * vec3(objectColor), objectColor.w);
}