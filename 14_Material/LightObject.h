#ifndef __LIGHT_OBJECT_H__
#define __LIGHT_OBJECT_H__


#include "SpotLight.h"
#include "RenderableObject.h"

class LightObject : public RenderableObject
{
private:
	SpotLight& _light;
public:
	LightObject(
		SpotLight& light,
		Renderable* model = nullptr
	);

	virtual void render(GLuint program) override;

	inline SpotLight& getLight() noexcept {
		return _light;
	}

	inline const SpotLight& getLight() const noexcept {
		return _light;
	}
};

#endif