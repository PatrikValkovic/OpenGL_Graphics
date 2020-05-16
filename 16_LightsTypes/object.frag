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

uniform uint n_lights;
uniform LightDefinition lights[20];
uniform vec3 camera_view_direction;
uniform Material material;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;



void main() {
	// get colors from textures
	vec3 objectColor = vec3(texture(diffuse_texture, TextureCoord));
	vec3 specularStrength = vec3(texture(specular_texture, TextureCoord));

	// ambient light
	vec3 ambient = ambient_color * ambient_strength * objectColor;
	vec3 tmpcolor = ambient;
	
	for(int i=0;i<n_lights;i++){
		// light
		LightDefinition light = lights[i];
		vec3 light_influence;
		if(light.type == 1){ // point light
			float lightStrength = light.parameters[0];
			float constant_att = light.parameters[1];
			float linear_att = light.parameters[2];
			float quadratic_att = light.parameters[3];

			// distance between fragment and light
			vec3 fragmentLight = light.position - FragmentPosition;
			float dist = length(fragmentLight);
			float distanceReduction = 1.0 / (constant_att + linear_att * dist + quadratic_att * dist * dist);

			// diffuse
			vec3 norm = normalize(Normal);
			vec3 lightDirection = normalize(fragmentLight);
			float diffuseStrength = max(dot(norm, lightDirection), 0.0f);
			vec3 diffuse = diffuseStrength * light.color;
	
			// specular
			vec3 viewDir = normalize(camera_view_direction);
			vec3 reflectDir = reflect(-lightDirection, norm);
			float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
			float spec = pow(viewReflectAngle, material.shininess);
			//vec3 specular_self = light.strength * distanceReduction * spec * objectColor * material.specular_self;
			//vec3 specular_light = light.strength * distanceReduction * spec * light.color * material.specular_light;
			vec3 specular = spec * specularStrength;

			light_influence = (diffuse + specular) * distanceReduction * objectColor * lightStrength;
		}
		if(light.type == 2){ // directional light
			float lightStrength = light.parameters[0];

			// diffuse
			vec3 norm = normalize(Normal);
			vec3 lightDirection = normalize(-light.direction);
			float diffuseStrength = max(dot(norm, lightDirection), 0.0f);
			vec3 diffuse = diffuseStrength * light.color;

			// specular
			vec3 viewDir = normalize(camera_view_direction);
			vec3 reflectDir = reflect(-lightDirection, norm);
			float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
			float spec = pow(viewReflectAngle, material.shininess);
			vec3 specular = spec * specularStrength;

			light_influence = (diffuse + specular) * objectColor * lightStrength;
		}
		if(light.type == 3){ // spotlight
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
			vec3 lightDirection = normalize(-light.direction);
			vec3 fragmentLight = light.position - FragmentPosition;
			float dist = length(fragmentLight);
			float between = dot(normalize(fragmentLight), lightDirection);

			float intensity = clamp((between - outerCutoff) / (innerCutoff - outerCutoff), 0.0, 1.0);
			float attenuation = 1.0 / (constant_att + linear_att * dist + quadratic_att * dist * dist);

			// diffuse 
			float diffuseStrength = max(dot(norm, fragmentLight), 0.0);
			vec3 diffuse = diffuseStrength * light.color;
		
			// specular
			vec3 viewDir = normalize(camera_view_direction);
			vec3 reflectDir = reflect(-lightDirection, norm);
			float viewReflectAngle = max(dot(-viewDir, reflectDir), 0.0f);
			float spec = pow(viewReflectAngle, material.shininess);
			vec3 specular = spec * specularStrength;

			light_influence = (diffuse + specular) * objectColor * lightStrength * intensity * attenuation;
		}
		tmpcolor = tmpcolor + light_influence;
	}

	color = vec4(tmpcolor, 1.0);
}