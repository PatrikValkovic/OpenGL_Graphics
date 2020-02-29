#include <iostream>
#include <SDL.h>
#include "RAII.h"
#include "SDLsupport.h"
#include "MainLoop.h"

int main(int argc, char** args)
{
	try {
		// load everything
		RAII<void> sdlRaii = load_sdl(SDL_INIT_VIDEO, false);
		RAII<SDL_Window*> window = create_window("05 - rotating rectangle", 1000, 100, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		RAII<SDL_GLContext> context = create_context(window);

		MainLoop loop(window);
		loop.compile_program();
		loop.loop();

		return 0;
	}
	catch (std::exception e) {
		std::cerr << "Unhandled exception: " << e.what() << std::endl;
		return 1;
	}
}