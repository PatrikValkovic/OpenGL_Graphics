#version 440 core

out vec4 color;

struct LightDefinition {
	uint type;
	vec3 position;
	vec3 direction;
	vec3 color;
	float parameters[8];
};

struct Material {
	vec3 diffuse;
	vec3 specular;
	float specular_self;
	float specular_light;
	float shininess;
};

in vec3 Normal;
in vec3 FragmentPosition;
in vec2 TextureCoord;

uniform float ambient_strength;
uniform vec3 ambient_color;

uniform LightDefinition light;
uniform vec3 camera_view_direction;
uniform Material material;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;



void main() {
	
	float distanceCoeficient = light.parameters[0];
	float lightStrength = light.parameters[1];

	// get colors from textures
	vec3 objectColor = vec3(texture(diffuse_texture, TextureCoord));
	vec3 specularStrength = vec3(texture(specular_texture, TextureCoord));

	// ambient light
	vec3 ambient = ambient_color * ambient_strength * objectColor;
	
	// distance between fragment and light
	vec3 fragmentLight = light.position - FragmentPosition;
	float dist = length(fragmentLight);
	float distanceReduction = max(0.0f, (distanceCoeficient - dist) / distanceCoeficient);

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(fragmentLight);
	float diffuseStrength = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = diffuseStrength * lightStrength * light.color * distanceReduction * objectColor;
	
	// specular
	vec3 viewDir = normalize(camera_view_direction);
	vec3 reflectDir = reflect(-lightDirection, norm);
	float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
	float spec = pow(viewReflectAngle, material.shininess);
	//vec3 specular_self = light.strength * distanceReduction * spec * objectColor * material.specular_self;
	//vec3 specular_light = light.strength * distanceReduction * spec * light.color * material.specular_light;
	vec3 specular = lightStrength * distanceReduction * spec * objectColor * specularStrength;
	

	color = vec4(ambient + diffuse + specular, 1.0f);
}