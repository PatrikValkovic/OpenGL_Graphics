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







////////////////////////////
//// MaterialDefinition ////
////////////////////////////

struct MaterialDefinition {
	vec3 diffuse;
	vec3 specular;
	float specular_self;
	float specular_light;
	float shininess;
};


////////////////////////////////
//// END MaterialDefinition ////
////////////////////////////////



out vec4 color;


in vec3 Normal;
in vec3 FragmentPosition;
in vec2 TextureCoord;

uniform float ambient_strength;
uniform vec3 ambient_color;

uniform vec3 camera_view_direction;
uniform MaterialDefinition material;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;

layout (std430, binding=3) buffer LightsBuffer {
	LightDefinition lights[];
};

vec3 compute_point_light(LightDefinition light, vec3 fragmentColor, vec3 specularStrength);
vec3 compute_direction_light(LightDefinition light, vec3 fragmentColor, vec3 specularStrength);
vec3 compute_spot_light(LightDefinition light, vec3 fragmentColor, vec3 specularStrength);


void main() {
	// get colors from textures
	vec3 objectColor = vec3(texture(diffuse_texture, TextureCoord));
	vec3 specularStrength = vec3(texture(specular_texture, TextureCoord));

	// ambient light
	vec3 ambient = ambient_color * ambient_strength * objectColor;
	vec3 tmpcolor = ambient;
	
	for(int i=0;i<lights.length();i++)
	{
		vec3 light_influence;
		switch(lights[i].type){
			case 1:
				light_influence = compute_point_light(lights[i], objectColor, specularStrength);
				break;
			case 2:
				light_influence = compute_direction_light(lights[i], objectColor, specularStrength);
				break;
			case 3:
				light_influence = compute_spot_light(lights[i], objectColor, specularStrength);
				break;
			default:
				light_influence = vec3(0.9, 0.156, 0.8125);
				break;
		}
		tmpcolor = tmpcolor + light_influence;
	}

	color = vec4(tmpcolor, 1.0);
}




vec3 compute_point_light(LightDefinition light, vec3 fragmentColor, vec3 specularStrength) {
	float lightStrength = light.parameters[0];
	float constant_att = light.parameters[1];
	float linear_att = light.parameters[2];
	float quadratic_att = light.parameters[3];

	// distance between fragment and light
	vec3 fragmentLight = vec3(light.position) - FragmentPosition;
	float dist = length(fragmentLight);
	float distanceReduction = 1.0 / (constant_att + linear_att * dist + quadratic_att * dist * dist);

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(fragmentLight);
	float diffuseStrength = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = diffuseStrength * vec3(light.color);
	
	// specular
	vec3 viewDir = normalize(camera_view_direction);
	vec3 reflectDir = reflect(-lightDirection, norm);
	float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
	float spec = pow(viewReflectAngle, 32);
	//vec3 specular_self = light.strength * distanceReduction * spec * objectColor * material.specular_self;
	//vec3 specular_light = light.strength * distanceReduction * spec * light.color * material.specular_light;
	vec3 specular = spec * specularStrength;

	return (diffuse + specular) * distanceReduction * fragmentColor * lightStrength;
}

vec3 compute_direction_light(LightDefinition light, vec3 fragmentColor, vec3 specularStrength){
	float lightStrength = light.parameters[0];

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(vec3(-light.direction));
	float diffuseStrength = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = diffuseStrength * vec3(light.color);

	// specular
	vec3 viewDir = normalize(camera_view_direction);
	vec3 reflectDir = reflect(-lightDirection, norm);
	float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
	float spec = pow(viewReflectAngle, 32);
	vec3 specular = spec * specularStrength;

	return (diffuse + specular) * fragmentColor * lightStrength;
}

vec3 compute_spot_light(LightDefinition light, vec3 fragmentColor, vec3 specularStrength) {
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
	vec3 fragmentLight = vec3(light.position) - FragmentPosition;
	float dist = length(fragmentLight);
	float between = dot(normalize(fragmentLight), lightDirection);

	float intensity = clamp((between - outerCutoff) / (innerCutoff - outerCutoff), 0.0, 1.0);
	float attenuation = 1.0 / (constant_att + linear_att * dist + quadratic_att * dist * dist);

	// diffuse 
	float diffuseStrength = max(dot(norm, fragmentLight), 0.0);
	vec3 diffuse = diffuseStrength * vec3(light.color);
		
	// specular
	vec3 viewDir = normalize(camera_view_direction);
	vec3 reflectDir = reflect(-lightDirection, norm);
	float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
	float spec = pow(viewReflectAngle, 32);
	vec3 specular = spec * specularStrength;

	return (diffuse + specular) * fragmentColor * lightStrength * intensity * attenuation;
}
