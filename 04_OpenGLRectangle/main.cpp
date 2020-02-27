#include <iostream>
#include <thread>
#include <chrono>
#include <SDL.h>
#include <glad.h>
#include "ShadersSupport.h"
#include "RAII.h"

int main(int argc, char** args)
{
	// load everything
	SDL_SetMainReady();
	RAII<void> sdlRaii(SDL_Quit, SDL_Init, SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("03 / OpenGL Rendering",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_OPENGL);
	RAII<SDL_Window*> windowRaii(SDL_DestroyWindow, window);
	RAII<SDL_GLContext> context(SDL_GL_DeleteContext, SDL_GL_CreateContext, window);
	gladLoadGL();

	// compile shaders
	RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "vs.vert", GL_VERTEX_SHADER);
	RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "fs.frag", GL_FRAGMENT_SHADER);

	// create program
	RAII<GLuint> program(glDeleteProgram, glCreateProgram);
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	fragmentShader.free();
	vertexShader.free();

	// create geometry
	GLuint vertexArrayObject = 0;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	RAII<GLuint> vertexArrayObjectRaii([](GLuint v) {glDeleteVertexArrays(1, &v); }, (GLuint)0);

	// main loop
	SDL_Event e;
	bool keep_running = true;
	while (keep_running) {
		// handle events
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				keep_running = false;
		}

		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL we'd like to use the previously compiled shader program
		glUseProgram(program);
		// Draw the scene geometry - just tell OpenGL we're drawing at this point
		glPointSize(10.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(window);
	}

	return 0;
}