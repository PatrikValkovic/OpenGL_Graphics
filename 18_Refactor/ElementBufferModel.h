#ifndef __ELEMENT_BUFFER_MODEL_H__
#define __ELEMENT_BUFFER_MODEL_H__
#include "BaseModel.h"

class ElementBufferModel: public BaseModel
{
protected:
	RAIIArray<> _elementBuffer;
	unsigned int _numOfElements;
public:
	ElementBufferModel();
	ElementBufferModel(const ElementBufferModel&) = delete;
	ElementBufferModel(ElementBufferModel&&) = default;
	ElementBufferModel& operator=(const ElementBufferModel&) = delete;
	ElementBufferModel& operator=(ElementBufferModel&&) = default;
	virtual ~ElementBufferModel() = default;
};

#endif