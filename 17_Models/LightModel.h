#ifndef __LIGHT_MODEL_H__
#define __LIGHT_MODEL_H__

#include "ElementBufferModel.h"

class LightModel : public ElementBufferModel
{
public:
	LightModel();

	virtual void render(GLuint program) override;

};

#endif