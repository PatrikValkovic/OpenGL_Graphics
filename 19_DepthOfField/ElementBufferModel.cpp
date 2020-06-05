#include "ElementBufferModel.h"

ElementBufferModel::ElementBufferModel()
	: BaseModel(), _elementBuffer(glDeleteBuffers, glGenBuffers), _numOfElements(0)
{

}
