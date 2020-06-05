#include "Materials.h"

/**
 * Source: http://devernay.free.fr/cours/opengl/materials.html
 */


Material MATERIALS::emerald(
	glm::vec3(0.07568f, 0.61424f, 0.07568), //diffuse color
	glm::vec3(0.633f, 0.727811f, 0.633f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.6f * 128.0f // shininess
);

Material MATERIALS::jade(
	glm::vec3(0.54f, 0.89f, 0.63f), //diffuse color
	glm::vec3(0.316228f, 0.316228f, 0.316228f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.1f * 128.0f // shininess
);

Material MATERIALS::obsidian(
	glm::vec3(0.18275f, 0.17f, 0.22525f), //diffuse color
	glm::vec3(0.332741f, 0.328634f, 0.346435f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.3f * 128.0f // shininess
);

Material MATERIALS::pearl(
	glm::vec3(1.0f, 0.829f, 0.829f), //diffuse color
	glm::vec3(0.296648f, 0.296648f, 0.296648f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.088f * 128.0f // shininess
);

Material MATERIALS::ruby(
	glm::vec3(0.61424f, 0.04136f, 0.04136f), //diffuse color
	glm::vec3(0.727811f, 0.626959f, 0.626959f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.6f * 128.0f // shininess
);

Material MATERIALS::turquoise(
	glm::vec3(0.396f, 0.74151f, 0.69102f), //diffuse color
	glm::vec3(0.297254f, 0.30829f, 0.306678f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.1f * 128.0f // shininess
);

Material MATERIALS::brass(
	glm::vec3(0.780392f, 0.568627f, 0.113725f), //diffuse color
	glm::vec3(0.992157f, 0.941176f, 0.807843f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.21794872f * 128.0f // shininess
);

Material MATERIALS::bronze(
	glm::vec3(0.714f, 0.4284f, 0.18144f), //diffuse color
	glm::vec3(0.393548f, 0.271906f, 0.166721f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.2f * 128.0f // shininess
);

Material MATERIALS::chrome(
	glm::vec3(0.4f, 0.4f, 0.4f), //diffuse color
	glm::vec3(0.774597f, 0.774597f, 0.774597f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.6f * 128.0f // shininess
);

Material MATERIALS::copper(
	glm::vec3(0.7038f, 0.27048f, 0.0828f), //diffuse color
	glm::vec3(0.256777f, 0.137622f, 0.086014f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.1f * 128.0f // shininess
);

Material MATERIALS::gold(
	glm::vec3(0.75164f, 0.60648f, 0.22648f), //diffuse color
	glm::vec3(0.628281f, 0.555802f, 0.366065f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.4f * 128.0f // shininess
);

Material MATERIALS::silver(
	glm::vec3(0.50754f, 0.50754f, 0.50754f), //diffuse color
	glm::vec3(0.508273f, 0.508273f, 0.508273f), // specular color
	1.0f, // specular self
	0.0f, // specular light
	0.4f * 128.0f // shininess
);

