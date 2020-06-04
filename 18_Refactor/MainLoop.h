#ifndef __MAIN_LOOP_H__
#define __MAIN_LOOP_H__
#include <SDL.h>
#include <glad/glad.h>
#include "RAII.h"

class MainLoop
{
private:
	SDL_Window* _window;
	RAII<GLuint> _backgroundProgram;
	RAII<GLuint> _mainProgram;
public:
	MainLoop(SDL_Window* win);
	void compile_program();
	void loop();
};

#endif