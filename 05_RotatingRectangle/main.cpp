#include <iostream>
#include <SDL.h>
#include <glad/glad.h>
#include "SDLsupport.h"
#include "ShadersSupport.h"
#include "RAII.h"

int main(int argc, char** args)
{
	try {
		// load everything
		RAII<void> sdlRaii = load_sdl(SDL_INIT_VIDEO, false);
		RAII<SDL_Window*> window = create_window("05 - rotating rectangle", 1000, 100, 800, 600, SDL_WINDOW_OPENGL);
		RAII<SDL_GLContext> context = create_context(window);

		// compile shaders
		RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "vs.vert", GL_VERTEX_SHADER);
		RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "fs.frag", GL_FRAGMENT_SHADER);

		// create program
		RAII<GLuint> program(glDeleteProgram, glCreateProgram);
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		link_program(program);
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
			glClear(GL_COLOR_BUFFER_BIT);
			// Tell OpenGL we'd like to use the previously compiled shader program
			glUseProgram(program);
			// Draw the scene geometry - just tell OpenGL we're drawing at this point
			glPointSize(10.0f);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			SDL_GL_SwapWindow(window);
		}

		return 0;
	}
	catch (std::exception e) {
		std::cerr << "Unhandled exception " << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}