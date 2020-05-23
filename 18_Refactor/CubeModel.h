#ifndef __CUBE_MODEL_H__
#define __CUBE_MODEL_H__

#include "ElementBufferModel.h"

class CubeModel : public ElementBufferModel
{
public:
	CubeModel();
	virtual void render(GLuint program) override;
};


#endif