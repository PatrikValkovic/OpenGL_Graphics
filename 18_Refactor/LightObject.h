#ifndef __LIGHT_OBJECT_H__
#define __LIGHT_OBJECT_H__
#include "BaseLight.h"
#include "BaseObject.h"

class LightObject : public BaseObject
{
private:
	const BaseLight& _light;
public:
	LightObject(
		const BaseLight& light,
		glm::vec3 translate = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		glm::mat3 rotate = glm::mat3(1.0f)
	);

	inline const BaseLight& getLight() const noexcept {
		return _light;
	}
};

#endif