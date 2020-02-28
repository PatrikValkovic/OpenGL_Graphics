#include <iostream>
#include <thread>
#include <chrono>
#include <SDL.h>
#include <glad/glad.h>

int main(int argc, char** arg) {

	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("02 - OpenGL Startup example",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_OPENGL
	);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		std::cerr << "Coudn't create OpenGL Context" << std::endl;
		return 1;
	}
	gladLoadGL(); // needs to be after creation of context

	std::cout << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}