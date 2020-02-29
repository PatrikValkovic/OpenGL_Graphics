#include "SDLsupport.h"
#include <iostream>
#include <glad/glad.h>

RAII<void> load_sdl(unsigned int flags, bool main_ready)
{
	if (!main_ready)
		SDL_SetMainReady();

	if (SDL_Init(flags) != 0) {
		std::cerr << SDL_GetError() << std::endl;
		throw LoadException("Can't load SDL");
	}
	return RAII<void>(SDL_Quit);
}

RAII<SDL_Window*> create_window(std::string title, int x, int y, int w, int h, unsigned int flags)
{
	SDL_Window* win = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
	if (win == nullptr) {
		std::cerr << SDL_GetError() << std::endl;
		throw LoadException("Can't create window");
	}
	return RAII<SDL_Window*>(SDL_DestroyWindow, win);
}

RAII<SDL_GLContext> create_context(SDL_Window* window)
{
	// create context
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		std::cerr << SDL_GetError() << std::endl;
		throw LoadException("Coudn't load OpenGL context");
	}
	RAII<SDL_GLContext> contextRaii(SDL_GL_DeleteContext, context);

	// laod extensions
	if (!gladLoadGL()) {
		throw LoadException("Can't load OpenGL extension by glad");
	}

	// enable logging
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback([](
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam) {
			using namespace std;
			if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM) {
				cerr << "Error in OpenGL: " << message << endl << "\tof type 0x" << hex << type << " from source 0x" << source << endl;
			}
			else {
				cout << "OpenGL log: " << message << endl;
			}
	}, nullptr);

	std::cout << "OpenGL Version:" << glGetString(GL_VERSION) << std::endl << "Extensions: ";
	GLint n = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	for (int i = 0; i < n; i++) {
		std::cout << glGetStringi(GL_EXTENSIONS, i) << " ";
	}
	std::cout << std::endl;

	return contextRaii;
}
