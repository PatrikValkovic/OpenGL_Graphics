#ifndef __LIGHT_DEFINITION_H__
#define __LIGHT_DEFINITION_H__ 
#include "Constants.h"

/////////////////////////
//// LightDefinition ////
/////////////////////////

struct LightDefinition {
	float parameters[MAX_LIGHT_PARAMETERS];
	vec4 position;
	vec4 direction;
	vec4 color;
	uint type;
};

/////////////////////////////
//// END LightDefinition ////
/////////////////////////////

#endif
