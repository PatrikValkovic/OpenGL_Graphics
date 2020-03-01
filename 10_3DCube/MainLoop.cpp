#include "MainLoop.h"
#include <chrono>
#include <iostream>
#include <SDL_image.h>
#include <gtc/matrix_transform.hpp>
#include "ShadersSupport.h"
#include "SDLsupport.h"
#include "FPSCounter.h"
#include "HouseModel.h"

MainLoop::MainLoop(SDL_Window* win) : _window(win)
{}

void MainLoop::compile_program()
{
	// compile shaders
	RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "learngl.vert", GL_VERTEX_SHADER);
	RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "learngl.frag", GL_FRAGMENT_SHADER);

	// create program
	_program = RAII<GLuint>(glDeleteProgram, glCreateProgram);
	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragmentShader);
	link_program(_program);
}

void MainLoop::loop()
{
	RAIIArray<> wallTexture = load_texture("wall.jpg");
	RAIIArray<> roofTexture = load_texture("roof.jpg");


	// CONFIGURE
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClearDepth(1.0);
	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// enable depth
	glEnable(GL_DEPTH_TEST);

	FPSCounter fps;
	HouseModel house(wallTexture, roofTexture);
	float rotation = 0.0;

	// main loop
	SDL_Event e;
	bool keep_running = true;
	while (keep_running) {
		// handle events
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				keep_running = false;
		}

		fps.tick();
		double delta_time = fps.getDelta();

		rotation += 30 * (float)delta_time;
		if (rotation > 360) rotation -= 360;

		// Set up viewport
		int w, h;
		SDL_GetWindowSize(_window, &w, &h);
		glViewport(0, 0, w, h);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use program
		glUseProgram(_program);

		// render
		glm::mat4 projective = glm::perspective(glm::degrees(45.0f), 8.0f / 6.0f, 0.1f, 200.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.3f));
		model = glm::rotate(model, glm::radians(rotation), glm::normalize(glm::vec3(0.6f, 0.1f, -0.2f)));
		house.render(_program, model, glm::mat4(1.0f), projective);

		// Swap the buffers
		SDL_GL_SwapWindow(_window);
	}
}
