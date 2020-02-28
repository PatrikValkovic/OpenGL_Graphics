#include "SDLsupport.h"
#include <iostream>
#include <glad/glad.h>

RAII<void> load_sdl(unsigned int flags, bool main_ready) throw(LoadException)
{
	if (!main_ready)
		SDL_SetMainReady();

	if (SDL_Init(flags) != 0) {
		std::cerr << SDL_GetError() << std::endl;
		throw LoadException("Can't load SDL");
	}
	return RAII<void>(SDL_Quit);
}

RAII<SDL_Window*> create_window(std::string title, int x, int y, int w, int h, unsigned int flags) throw(LoadException)
{
	SDL_Window* win = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
	if (win == nullptr) {
		std::cerr << SDL_GetError() << std::endl;
		throw LoadException("Can't create window");
	}
	return RAII<SDL_Window*>(SDL_DestroyWindow, win);
}

RAII<SDL_GLContext> create_context(SDL_Window* window) throw(LoadException)
{
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		std::cerr << SDL_GetError() << std::endl;
		throw LoadException("Coudn't load OpenGL context");
	}
	RAII<SDL_GLContext> contextRaii(SDL_GL_DeleteContext, context);

	if (!gladLoadGL()) {
		throw LoadException("Can't load OpenGL extension by glad");
	}

	std::cout << "OpenGL Version:" << glGetString(GL_VERSION) << std::endl << "Extensions: ";
	GLint n = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	for (int i = 0; i < n; i++) {
		std::cout << glGetStringi(GL_EXTENSIONS, i) << " ";
	}
	std::cout << std::endl;

	return contextRaii;
}
