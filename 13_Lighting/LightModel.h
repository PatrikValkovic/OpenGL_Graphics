#ifndef __LIGHT_MODEL_H__
#define __LIGHT_MODEL_H__

#include "BaseModel.h"

class LightModel : public BaseModel
{
private:
	RAIIArray<> _elementBuffer;
public:
	LightModel();
	virtual void render(GLuint program, glm::mat4* model = nullptr, glm::mat4* view = nullptr, glm::mat4* projection = nullptr) override;

};

#endif