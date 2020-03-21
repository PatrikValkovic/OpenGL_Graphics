#ifndef __CUBE_MODEL_H__
#define __CUBE_MODEL_H__

#include "BaseModel.h"

class CubeModel : public BaseModel
{
private:
	RAIIArray<> _elementBuffer;
public:
	CubeModel();
	virtual void render(GLuint program) const override;
};


#endif