#ifndef __LIGHT_OBJECT_H__
#define __LIGHT_OBJECT_H__


#include "BaseLight.h"
#include "RenderableObject.h"

class LightObject : public RenderableObject
{
private:
	const BaseLight& _light;
public:
	LightObject(const BaseLight& light);
	LightObject(const BaseLight& light, const Renderable& inner);

	virtual void render(GLuint program) const override;

	inline const BaseLight& getLight() const noexcept {
		return _light;
	}
};

#endif