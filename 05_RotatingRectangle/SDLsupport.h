#ifndef __SDL_SUPPORT_H__
#define __SDL_SUPPORT_H__

#include <string>
#include <exception>
#include <SDL.h>
#include "RAII.h"

using LoadException = std::exception;

RAII<void> load_sdl(unsigned int flags, bool main_ready = true) throw(LoadException);

RAII<SDL_Window*> create_window(std::string title, 
	int x=SDL_WINDOWPOS_CENTERED, int y=SDL_WINDOWPOS_CENTERED, 
	int w=800, int h=600, 
	unsigned int flags = 0) throw(LoadException);

RAII<SDL_GLContext> create_context(SDL_Window* window) throw(LoadException);

#endif