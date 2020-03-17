#include "MainLoop.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <SDL_image.h>
#include <gtc/matrix_transform.hpp>
#include "ShadersSupport.h"
#include "SDLsupport.h"
#include "FPSCounter.h"
#include "CubeModel.h"
#include "SimCamera.h"
#include "FlyCamera.h"
#include "RenderableObject.h"
#include "LightModel.h"
#include "AmbientLight.h"
#include "LightsWrapper.h"

MainLoop::MainLoop(SDL_Window* win) : _window(win)
{}

void MainLoop::compile_program() 
{
	// compile shaders
	{
		RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "object.vert", GL_VERTEX_SHADER);
		RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "object.frag", GL_FRAGMENT_SHADER);
		// create program
		_objectProgram = RAII<GLuint>(glDeleteProgram, glCreateProgram);
		glAttachShader(_objectProgram, vertexShader);
		glAttachShader(_objectProgram, fragmentShader);
		link_program(_objectProgram);
	}

	// compile light program
	{
		RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "light.vert", GL_VERTEX_SHADER);
		RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "light.frag", GL_FRAGMENT_SHADER);
		_lightProgram = RAII<GLuint>(glDeleteProgram, glCreateProgram);
		glAttachShader(_lightProgram, vertexShader);
		glAttachShader(_lightProgram, fragmentShader);
		link_program(_lightProgram);
	}
}

void MainLoop::loop()
{
	// CONFIGURE
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClearDepth(1.0);
	// enable depth
	glEnable(GL_DEPTH_TEST);

	float movement_speed = 2.5f;
	float rotation_speed = 60;
	float mouse_sensitivity = 0.4f;
	float ambient_strength_speed = 0.2f;
	float ambient_color_speed = 0.25f;

	FPSCounter fps;
	std::unique_ptr<BaseCamera> c = std::make_unique<FlyCamera>(glm::vec3(0, 1, 0), glm::vec3(1, 1, 2));
	std::unique_ptr<BaseModel> cube = std::make_unique<CubeModel>();
	std::unique_ptr<BaseModel> light_model = std::make_unique<LightModel>();
	SpotLight spot_light(1.4f);
	std::vector<std::unique_ptr<RenderableObject>> toRender;
	toRender.push_back(std::make_unique<RenderableObject>(cube.get(), glm::vec3(0, 0, 0)));
	toRender.push_back(std::make_unique<RenderableObject>(cube.get(), glm::vec3(0, -1.5f, 0), glm::vec3(40.0f, 0.1f, 40.0f)));
	std::vector<LightObject> lights {
		LightObject(spot_light, light_model.get())
	};
	lights[0].setPosition(glm::vec3(1.5f, 2.0f, -3.f));
	lights[0].setScale(glm::vec3(0.2f));
	AmbientLight ambient(0.4f);
	LightsWrapper lights_wrapper;

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
			if (e.type == SDL_MOUSEMOTION && SDL_GetRelativeMouseMode() == SDL_TRUE) {
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
				if (e.key.keysym.scancode == SDL_SCANCODE_F5)
					SDL_SetRelativeMouseMode(static_cast<SDL_bool>(!SDL_GetRelativeMouseMode()));
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
		if (keyboard_state[SDL_SCANCODE_PAGEUP]) ambient.updateStrength(delta_time * ambient_strength_speed);
		if (keyboard_state[SDL_SCANCODE_PAGEDOWN]) ambient.updateStrength(-delta_time * ambient_strength_speed);
		if (keyboard_state[SDL_SCANCODE_T]) ambient.updateRed(delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_G]) ambient.updateGreen(delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_B]) ambient.updateBlue(delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_Y]) ambient.updateRed(-delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_H]) ambient.updateGreen(-delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_N]) ambient.updateBlue(-delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_1]) spot_light.updateRed(delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_4]) spot_light.updateRed(-delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_2]) spot_light.updateGreen(delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_5]) spot_light.updateGreen(-delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_3]) spot_light.updateBlue(delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_6]) spot_light.updateBlue(-delta_time * ambient_color_speed);
		if (keyboard_state[SDL_SCANCODE_7]) spot_light.updateStrength(delta_time * ambient_strength_speed);
		if (keyboard_state[SDL_SCANCODE_8]) spot_light.updateStrength(-delta_time * ambient_strength_speed);
		if (keyboard_state[SDL_SCANCODE_9]) spot_light.updateDistance(delta_time * ambient_strength_speed);
		if (keyboard_state[SDL_SCANCODE_0]) spot_light.updateDistance(-delta_time * ambient_strength_speed);
		if (keyboard_state[SDL_SCANCODE_I]) lights[0].moveZ(delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_K]) lights[0].moveZ(-delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_J]) lights[0].moveX(-delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_L]) lights[0].moveX(delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_O]) lights[0].moveY(delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_U]) lights[0].moveY(-delta_time * movement_speed);

		// Set up viewport
		int w, h;
		SDL_GetWindowSize(_window, &w, &h);
		glViewport(0, 0, w, h);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// compute transformations
		glm::mat4 projective = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 200.0f);
		glm::mat4 view = c->createTransformMatrix();

		// render light
		lights_wrapper.clear();
		RenderableObject::transformations(_lightProgram, nullptr, &view, &projective);
		for (LightObject& obj : lights) {
			obj.render(_lightProgram);
			lights_wrapper.addLight(obj);
		}

		// render objects
		ambient.use(_objectProgram);
		RenderableObject::transformations(_objectProgram, nullptr, &view, &projective);
		lights_wrapper.updateRendering(_objectProgram, *c);
		for (auto &obj : toRender) {
			obj->render(_objectProgram);
		}

		// Swap the buffers
		SDL_GL_SwapWindow(_window);
	}
}
