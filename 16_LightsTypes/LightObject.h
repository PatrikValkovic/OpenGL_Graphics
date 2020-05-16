#ifndef __LIGHT_OBJECT_H__
#define __LIGHT_OBJECT_H__


#include "PointLight.h"
#include "RenderableObject.h"

class LightObject : public RenderableObject
{
private:
	const PointLight& _light;
public:
	LightObject(const PointLight& light);
	LightObject(const PointLight& light, const Renderable& inner);

	virtual void render(GLuint program) const override;

	inline const PointLight& getLight() const noexcept {
		return _light;
	}
};

#endif