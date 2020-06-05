#ifndef __SCREEN_PLANE_MODEL_H__
#define __SCREEN_PLANE_MODEL_H__
#include "ElementBufferModel.h"

class ScreenPlaneModel : public ElementBufferModel
{
public:
	ScreenPlaneModel();
	virtual void render(GLuint program) override;
};

#endif