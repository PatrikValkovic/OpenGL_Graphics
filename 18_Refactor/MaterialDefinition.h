#ifndef __MATERIAL_DEFINITION_H__
#define __MATERIAL_DEFINITION_H__

struct MaterialDefinition {
	vec3 diffuse;
	vec3 specular;
	float specular_self;
	float specular_light;
	float shininess;
};


#endif