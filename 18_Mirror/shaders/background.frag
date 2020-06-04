#version 440 core
#include "Constants.h"

out vec4 color;


void main() {
	color = vec4(CLEAR_COLOR_X, CLEAR_COLOR_Y, CLEAR_COLOR_Z, 1.0f);
}