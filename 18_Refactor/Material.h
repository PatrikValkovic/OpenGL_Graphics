#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <glm.hpp>

class Material
{
protected:
	glm::vec3 _diffuse;
	glm::vec3 _specular;
	float _specularSelf;
	float _specularLight;
	float _shininess;
public:
	Material(glm::vec3 diffuseColor);
	Material(glm::vec3 diffuseColor, float specularSelf, float specularLight, float shininess = 32.f);
	Material(glm::vec3 diffuseColor, glm::vec3 specularColor, float specularSelf, float specularLight, float shininess = 32.0f);
	Material(const Material&) = default;
	Material(Material&&) = default;
	Material& operator=(const Material&) = default;
	Material& operator=(Material&&) = default;
	virtual ~Material() = default;

	inline glm::vec3 getDiffuseColor() const noexcept {
		return _diffuse;
	}
	inline Material& setDiffuseColor(glm::vec3 color) noexcept {
		_diffuse = glm::max(glm::min(color, glm::vec3(1.0f)), glm::vec3(0.0f));
		return *this;
	}
	inline Material& updateDiffuseColor(glm::vec3 shift) noexcept {
		return this->setDiffuseColor(this->getDiffuseColor() + shift);
	}

	inline glm::vec3 getSpecularColor() const noexcept {
		return _specular;
	}
	inline Material& setSpecularColor(glm::vec3 color) noexcept {
		_specular = glm::max(glm::min(color, glm::vec3(1.0f)), glm::vec3(0.0f));
		return *this;
	}
	inline Material& updateSpecularColor(glm::vec3 shift) noexcept {
		return this->setSpecularColor(this->getSpecularColor() + shift);
	}

	inline Material& setColor(glm::vec3 color, bool specular=true) noexcept {
		if (specular) {
			this->setSpecularColor(color);
		}
		return this->setDiffuseColor(color);
	}
	inline Material& updateColor(glm::vec3 shift, bool specular = true) noexcept {
		if (specular) {
			this->updateSpecularColor(shift);
		}
		return this->updateDiffuseColor(shift);
	}


	inline float getSpecularStrengthSelf() const noexcept {
		return _specularSelf;
	}
	inline float getSpecularStrengthLight() const noexcept {
		return _specularLight;
	}
	inline Material& setSpecularStrengthSelf(float value) noexcept {
		_specularSelf = value;
		return *this;
	}
	inline Material& setSpecularStrengthLight(float value) noexcept {
		_specularLight = value;
		return *this;
	}
	inline Material& updateSpecularStrengthSelf(float value) noexcept {
		return this->setSpecularStrengthSelf(this->getSpecularStrengthSelf() + value);
	}
	inline Material& updateSpecularStrengthLight(float value) noexcept {
		return this->setSpecularStrengthLight(this->getSpecularStrengthLight() + value);
	}
	inline Material& setSpecularStrength(float self, float light) noexcept {
		this->setSpecularStrengthSelf(self);
		return this->setSpecularStrengthLight(light);
	}
	inline Material& updateSpecularStrength(float self, float light) noexcept {
		float s = this->getSpecularStrengthSelf();
		float l = this->getSpecularStrengthLight();
		return this->setSpecularStrength(s + self, l + light);
	}


	inline float getShininess() const noexcept {
		return _shininess;
	}
	inline Material& setShininess(float value) noexcept {
		_shininess = value;
		return *this;
	}
	inline Material& updateShininess(float amount) noexcept {
		return this->setShininess(this->getShininess() + amount);
	}

	inline Material& setSpecular(glm::vec3 color) noexcept {
		return this->setSpecularColor(color);
	}
	inline Material& setSpecular(float self) noexcept {
		return this->setSpecularStrengthSelf(self);
	}
	inline Material& setSpecular(float self, float light) noexcept {
		return this->setSpecularStrength(self, light);
	}
	inline Material& setSpecular(float self, float light, float shinines) {
		this->setSpecular(self, light);
		return this->setShininess(shinines);
	}
	inline Material& setSpecular(glm::vec3 color, float self) {
		this->setSpecularColor(color);
		return this->setSpecularStrengthSelf(self);
	}
	inline Material& setSpecular(glm::vec3 color, float self, float light) {
		this->setSpecularColor(color);
		return this->setSpecularStrength(self, light);
	}
	inline Material& setSpecular(glm::vec3 color, float self, float light, float shininess) {
		this->setShininess(shininess);
		return this->setSpecular(color, self, light);
	}

};

#endif