#version 440 core








//////////////////
//// CONTANTS ////
//////////////////









///////////////////////
//// END CONSTANTS ////
///////////////////////




/////////////////////////
//// LightDefinition ////
/////////////////////////

struct LightDefinition {
	float parameters[8];
	vec4 position;
	vec4 direction;
	vec4 color;
	uint type;
};

/////////////////////////////
//// END LightDefinition ////
/////////////////////////////




in vec3 Normal;
in vec4 Color;
in vec3 Position;
in vec2 TextureCoords[4];

out vec4 color;

uniform sampler2D diffuse_texture;
uniform int diffuse_coord;
uniform sampler2D specular_texture;
uniform int specular_coord;
uniform sampler2D specular_self_texture;
uniform int specular_self_coord;
uniform sampler2D ambient_occlusion_texture;
uniform int ambient_occlusion_coord;
uniform sampler2D normal_texture;
uniform int normal_coord;
uniform sampler2D roughness_texture;
uniform int roughness_coord;

uniform vec3 camera_view_direction;
uniform float ambient_strength;
uniform vec3 ambient_color;
layout (std430, binding=3) buffer LightsBuffer {
	LightDefinition lights[];
};

vec3 compute_point_light(LightDefinition light, vec3 fragmentColor);
vec3 compute_direction_light(LightDefinition light, vec3 fragmentColor);
vec3 compute_spot_light(LightDefinition light, vec3 fragmentColor);

void main() {

	vec3 fragmentColor = vec3(Color);
	if(diffuse_coord >= 0){
		fragmentColor = vec3(texture(diffuse_texture, vec2(-1.0, -1.0) + TextureCoords[diffuse_coord]));
	}

	vec3 ambient = ambient_color * ambient_strength * fragmentColor;
	if(ambient_occlusion_coord >= 0){
		vec3 ambient_strength = vec3(texture(ambient_occlusion_texture, vec2(-1.0, -1.0) + TextureCoords[ambient_occlusion_coord]));
		ambient = ambient * ambient_strength;
	}

	vec3 tmpcolor = ambient;
	for(int i=0;i<lights.length();i++) {
		if(lights[i].type == 1)
			tmpcolor = tmpcolor + compute_point_light(lights[i], fragmentColor);
		else if(lights[i].type == 2)
			tmpcolor = tmpcolor + compute_direction_light(lights[i], fragmentColor);
		else if(lights[i].type == 3)
			tmpcolor = tmpcolor + compute_spot_light(lights[i], fragmentColor);
		else
			tmpcolor = vec3(0.9, 0.156, 0.8125);
	}


	color = vec4(tmpcolor, 1);
}


vec3 compute_point_light(LightDefinition light, vec3 fragmentColor) {
	float lightStrength = light.parameters[0];
	float constant_att = light.parameters[1];
	float linear_att = light.parameters[2];
	float quadratic_att = light.parameters[3];
	
	// distance between fragment and light
	vec3 fragmentLight = vec3(light.position) - Position;
	float dist = length(fragmentLight);
	float distanceReduction = 1.0 / (constant_att + linear_att * dist + quadratic_att * dist * dist);
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(fragmentLight);
	float diffuseStrength = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = diffuseStrength * vec3(light.color);
	
	// specular
	vec3 specular = vec3(0);
	if(specular_coord >= 0){
		vec3 specular_strength = vec3(texture(specular_texture, TextureCoords[specular_coord]));
		vec3 viewDir = normalize(camera_view_direction);
		vec3 reflectDir = reflect(-lightDirection, norm);
		float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
		vec3 shininess = vec3(16);
		if(roughness_coord >= 0){
			vec3 rougness = vec3(texture(roughness_texture, TextureCoords[roughness_coord]));
			shininess = 1.0f / rougness;
		}
		vec3 spec = pow(vec3(viewReflectAngle), shininess);
		specular = spec * specular_strength;
	}
	
	return (diffuse + specular) * distanceReduction * fragmentColor * lightStrength * vec3(light.color);
}

vec3 compute_direction_light(LightDefinition light, vec3 fragmentColor){
	float lightStrength = light.parameters[0];
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(vec3(-light.direction));
	float diffuseStrength = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = diffuseStrength * vec3(light.color);
	
	// specular
	vec3 specular = vec3(0);
	if(specular_coord >= 0){
		vec3 specular_strength = vec3(texture(specular_texture, TextureCoords[specular_coord]));
		vec3 viewDir = normalize(camera_view_direction);
		vec3 reflectDir = reflect(-lightDirection, norm);
		float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
		vec3 shininess = vec3(16);
		if(roughness_coord >= 0){
			vec3 rougness = vec3(texture(roughness_texture, TextureCoords[roughness_coord]));
			shininess = 1.0f / rougness;
		}
		vec3 spec = pow(vec3(viewReflectAngle), shininess);
		specular = spec * specular_strength;
	}
	
	return (diffuse  + specular) * fragmentColor * vec3(light.color) * lightStrength;
}

vec3 compute_spot_light(LightDefinition light, vec3 fragmentColor) {
	float lightStrength = light.parameters[0];
	float innerCutoff_angle = light.parameters[1];
	float outerCutoff_angle = light.parameters[2];
	float constant_att = light.parameters[3];
	float linear_att = light.parameters[4];
	float quadratic_att = light.parameters[5];
	float innerCutoff = cos(radians(innerCutoff_angle));
	float outerCutoff = cos(radians(outerCutoff_angle));
	
	// spotlight effect
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(-vec3(light.direction));
	vec3 fragmentLight = vec3(light.position) - Position;
	float dist = length(fragmentLight);
	float between = dot(normalize(fragmentLight), lightDirection);
	
	float intensity = clamp((between - outerCutoff) / (innerCutoff - outerCutoff), 0.0, 1.0);
	float attenuation = 1.0 / (constant_att + linear_att * dist + quadratic_att * dist * dist);
	
	// diffuse 
	float diffuseStrength = max(dot(norm, fragmentLight), 0.0);
	vec3 diffuse = diffuseStrength * vec3(light.color);

	// specular
	vec3 specular = vec3(0);
	if(specular_coord >= 0){
		vec3 specular_strength = vec3(texture(specular_texture, TextureCoords[specular_coord]));
		vec3 viewDir = normalize(camera_view_direction);
		vec3 reflectDir = reflect(-lightDirection, norm);
		float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
		vec3 shininess = vec3(16);
		if(roughness_coord >= 0){
			vec3 rougness = vec3(texture(roughness_texture, TextureCoords[roughness_coord]));
			shininess = 1.0f / rougness;
		}
		vec3 spec = pow(vec3(viewReflectAngle), shininess);
		specular = spec * specular_strength;
	}
	
	return (diffuse + specular) * fragmentColor * lightStrength * vec3(light.color) * intensity * attenuation;
}
