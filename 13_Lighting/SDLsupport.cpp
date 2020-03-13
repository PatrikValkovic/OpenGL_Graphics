#include "SDLsupport.h"
#include <iostream>
#include <glad/glad.h>
#include <SDL_image.h>

RAII<void> load_sdl(unsigned int flags, bool main_ready)
{
	if (!main_ready)
		SDL_SetMainReady();

	if (SDL_Init(flags) != 0) {
		std::cerr << SDL_GetError() << std::endl;
		throw LoadException("Can't load SDL");
	}

	unsigned int to_init = IMG_INIT_JPG | IMG_INIT_PNG;
	unsigned int initted = IMG_Init(to_init);
	if ((initted & to_init) != to_init) {
		std::cerr << IMG_GetError() << std::endl;
		throw LoadException("Can't load SDL Image library");
	}

	return RAII<void>([]() {
		IMG_Quit();
		SDL_Quit();
	});
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
	// set context version and compatibility mode
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
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

	// vsync
	SDL_GL_SetSwapInterval(0); // set 0 to disable vsync
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

	using namespace std;
	cout << "OpenGL Version:" << glGetString(GL_VERSION) << endl << "Extensions: ";
	GLint n = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	for (int i = 0; i < n; i++) {
		cout << glGetStringi(GL_EXTENSIONS, i) << " ";
	}
	GLint attributes = 0, unif = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributes);
	glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &unif);
	cout << endl << "Maximum number of vertex attributes " << attributes << endl;
	cout << "Maximum uniform locations: " << unif << endl;

	return contextRaii;
}
