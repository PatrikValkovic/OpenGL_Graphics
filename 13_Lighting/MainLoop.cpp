#include "MainLoop.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include <gtc/matrix_transform.hpp>
#include "ShadersSupport.h"
#include "SDLsupport.h"
#include "FPSCounter.h"
#include "HouseModel.h"
#include "SimCamera.h"
#include "FlyCamera.h"
#include "RenderableObject.h"

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
	std::unique_ptr<BaseModel> house = std::make_unique<HouseModel>(wallTexture, roofTexture);
	std::vector<RenderableObject> toRender{
		RenderableObject(*house, glm::vec3(0, 0, -2), glm::vec3(1), glm::vec3(0)),
		RenderableObject(*house, glm::vec3(1, 1, -3), glm::vec3(1), glm::vec3(0)),
		RenderableObject(*house, glm::vec3(-4, 0, -3), glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(0)),
		RenderableObject(*house, glm::vec3(-4, 0, -5), glm::vec3(2.0f, 1.0f, 1.0f), glm::vec3(0)),
		RenderableObject(*house, glm::vec3(-4, 0, -8), glm::vec3(1.0f, 1.0f, 2.0f), glm::vec3(0)),
		RenderableObject(*house, glm::vec3(-4, 0, -12), glm::vec3(1.5f, 1.5f, 1.5f), glm::vec3(0)),
		RenderableObject(*house, glm::vec3(-7, 0, -3), glm::vec3(1), glm::vec3(0.0f, 0.0f, 0.0f)),
		RenderableObject(*house, glm::vec3(-7, 0, -5), glm::vec3(1), glm::vec3(30.0f, 0.0f, 0.0f)),
		RenderableObject(*house, glm::vec3(-7, 0, -7), glm::vec3(1), glm::vec3(0.0f, 30.0f, 0.0f)),
		RenderableObject(*house, glm::vec3(-7, 0, -9), glm::vec3(1), glm::vec3(0.0f, 0.0f, 30.0f)),
		RenderableObject(*house, glm::vec3(-7, 0, -14), glm::vec3(1), glm::vec3(30.0f, 30.0f, 0.0f)),
		RenderableObject(*house, glm::vec3(-7, 0, -16), glm::vec3(1), glm::vec3(30.0f, 0.0f, 30.0f)),
		RenderableObject(*house, glm::vec3(-7, 0, -18), glm::vec3(1), glm::vec3(0.0f, 30.0f, 30.0f)),
		RenderableObject(*house, glm::vec3(-7, 0, -22), glm::vec3(1), glm::vec3(30.0f, 30.0f, 30.0f)),
		RenderableObject(*house, glm::vec3(-10, 0, -3), glm::vec3(1), glm::vec3(90.0f, 30.0f, 0.0f)),
		RenderableObject(*house, glm::vec3(-10, 0, -5), glm::vec3(1), glm::vec3(90.0f, 0.0f, 30.0f)),
		RenderableObject(*house, glm::vec3(-10, 0, -8), glm::vec3(1), glm::vec3(30.0f, 90.0f, 0.0f)),
		RenderableObject(*house, glm::vec3(-10, 0, -10), glm::vec3(1), glm::vec3(0.0f, 90.0f, 30.0f)),
		RenderableObject(*house, glm::vec3(-10, 0, -13), glm::vec3(1), glm::vec3(30.0f, 0.0f, 90.0f)),
		RenderableObject(*house, glm::vec3(-10, 0, -15), glm::vec3(1), glm::vec3(0.0f, 30.0f, 90.0f)),
	};
	std::unique_ptr<BaseCamera> c = std::make_unique<FlyCamera>(glm::vec3(0, 1, 0));
	float movement_speed = 2.5f;
	float rotation_speed = 60;
	float mouse_sensitivity = 0.4f;

	// main loop
	SDL_Event e;
	bool keep_running = true;
	while (keep_running) {

		fps.tick();
		float delta_time = (float)fps.getDelta();

		// handle events
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
				keep_running = false;
			}
			if (e.type == SDL_MOUSEMOTION) {
				c->lookUp((float)e.motion.yrel * mouse_sensitivity);
				c->lookRight((float)e.motion.xrel * mouse_sensitivity);
			}
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.scancode == SDL_SCANCODE_F1)
					glIsEnabled(GL_DEPTH_TEST) ? glDisable(GL_DEPTH_TEST) : glEnable(GL_DEPTH_TEST);
				if (e.key.keysym.scancode == SDL_SCANCODE_F2)
					glIsEnabled(GL_BLEND) ? glDisable(GL_BLEND) : glEnable(GL_BLEND);
				if (e.key.keysym.scancode == SDL_SCANCODE_F3)
					SDL_GL_SetSwapInterval(1 - SDL_GL_GetSwapInterval());
				if (e.key.keysym.scancode == SDL_SCANCODE_F4)
					glIsEnabled(GL_CULL_FACE) ? glDisable(GL_CULL_FACE) : glEnable(GL_CULL_FACE);
				if (e.key.keysym.scancode == SDL_SCANCODE_F11)
					c = std::make_unique<FlyCamera>(glm::vec3(0, 1, 0), c->getPos(), c->getViewDirection());
				if (e.key.keysym.scancode == SDL_SCANCODE_F10)
					c = std::make_unique<SimCamera>(c->getPos(), c->getViewDirection(), c->getCameraUp());
			}
		}
		Uint8 const* keyboard_state = SDL_GetKeyboardState(nullptr);
		if (keyboard_state[SDL_SCANCODE_W]) c->moveZ(delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_S]) c->moveZ(-delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_A]) c->moveX(-delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_D]) c->moveX(delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_R]) c->moveY(delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_F]) c->moveY(-delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_E]) c->rotateRight(delta_time * rotation_speed);
		if (keyboard_state[SDL_SCANCODE_Q]) c->rotateLeft(-delta_time * rotation_speed);

		// Set up viewport
		int w, h;
		SDL_GetWindowSize(_window, &w, &h);
		glViewport(0, 0, w, h);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use program
		glUseProgram(_program);

		// compute transformations
		glm::mat4 projective = glm::perspective(glm::degrees(45.0f), 8.0f / 6.0f, 0.1f, 200.0f);
		glm::mat4 view = c->createTransformMatrix();
		BaseModel::transformations(_program, nullptr, &view, &projective);

		// render
		for (RenderableObject& obj : toRender) {
			obj.render(_program);
		}

		// Swap the buffers
		SDL_GL_SwapWindow(_window);
	}
}
