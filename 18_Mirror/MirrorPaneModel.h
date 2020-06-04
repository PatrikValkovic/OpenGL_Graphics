#ifndef __MIRROR_PANE_MODEL_H__
#define __MIRROR_PANE_MODEL_H__
#include "ElementBufferModel.h"

class MirrorPaneModel : public ElementBufferModel
{
public:
	MirrorPaneModel();

	virtual void render(GLuint program) override;
};

#endif