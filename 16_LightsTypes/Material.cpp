#include "Material.h"

Material::Material(glm::vec3 diffuseColor)
	: Material(diffuseColor, 0.0f, 0.0f, 0.0f)
{}

Material::Material(glm::vec3 diffuseColor, float specularSelf, float specularLight, float shininess)
	: Material(diffuseColor, diffuseColor, specularSelf, specularLight, shininess)
{}

Material::Material(glm::vec3 diffuseColor, glm::vec3 specularColor, float specularSelf, float specularLight, float shininess)
	: _diffuse(diffuseColor), _specular(specularColor), _specularSelf(specularSelf), _specularLight(specularLight), _shininess(shininess)
{}
