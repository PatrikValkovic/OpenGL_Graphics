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
#include "LightModel.h"
#include "AmbientLight.h"
#include "LightsWrapper.h"
#include "Materials.h"
#include "MaterialRenderable.h"
#include "TextureRenderable.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Spotlight.h"
#include "LoadedModel.h"
#include "TexturedObject.h"

MainLoop::MainLoop(SDL_Window* win) : _window(win)
{}

void MainLoop::compile_program()
{
	// compile shaders
	{
		RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "shaders/object.vert", GL_VERTEX_SHADER);
		RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "shaders/object.frag", GL_FRAGMENT_SHADER);
		// create program
		_objectProgram = RAII<GLuint>(glDeleteProgram, glCreateProgram);
		glAttachShader(_objectProgram, vertexShader);
		glAttachShader(_objectProgram, fragmentShader);
		link_program(_objectProgram);
	}

	// compile light program
	{
		RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "shaders/light.vert", GL_VERTEX_SHADER);
		RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "shaders/light.frag", GL_FRAGMENT_SHADER);
		_lightProgram = RAII<GLuint>(glDeleteProgram, glCreateProgram);
		glAttachShader(_lightProgram, vertexShader);
		glAttachShader(_lightProgram, fragmentShader);
		link_program(_lightProgram);
	}

	// compile imported program
	{
		RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "shaders/imported.vert", GL_VERTEX_SHADER);
		RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "shaders/imported.frag", GL_FRAGMENT_SHADER);
		_importedProgram = RAII<GLuint>(glDeleteProgram, glCreateProgram);
		glAttachShader(_importedProgram, vertexShader);
		glAttachShader(_importedProgram, fragmentShader);
		link_program(_importedProgram);
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

	FPSCounter fps;
	std::unique_ptr<BaseCamera> c = std::make_unique<FlyCamera>(glm::vec3(0, 1, 0), glm::vec3(1, 1, 2));
	CubeModel cube_model;
	LightModel light_model;
	Spotlight spot_light(5.0f, 10.0f, glm::vec3(-1, -1, 4));
	PointLight point_light(glm::vec3(1.0, 0.14, 0.07), 2.0f);
	DirectionalLight direction_light(glm::vec3(1.0, -5.0, -2.0), glm::vec3(1.0, 1.0, 1.0), 1.0f);
	Texture texture_diffuse = Texture::fromFile("textures/container.png");
	Texture texture_specular = Texture::fromFile("textures/container_specular.png");
	TextureRenderable diffusedCube(cube_model, texture_diffuse, TextureSlots::Texture10, "diffuse_texture");
	TextureRenderable texturedCube(diffusedCube, texture_specular, TextureSlots::Texture11, "specular_texture");
	LoadedModel<> guitar("models/SurvivalBackPack/Survival_BackPack_2.fbx", _lightProgram);
	TexturedObject guitar_textured(guitar);
	guitar_textured
		.useTexture("models/SurvivalBackPack/1001_albedo.jpg", TextureTypes::diffuse, 0, false)
		.useTexture("models/SurvivalBackPack/1001_AO.jpg", TextureTypes::ambient_occlusion, 0, false)
		.useTexture("models/SurvivalBackPack/1001_metallic.jpg", TextureTypes::specular, 0, false)
		.useTexture("models/SurvivalBackPack/1001_normal.png", TextureTypes::normal, 0, false)
		.useTexture("models/SurvivalBackPack/1001_roughness.jpg", TextureTypes::rougness, 0, false);
	guitar_textured.setScale(glm::vec3(0.004f))
				   .setPosition(glm::vec3(-0.5,1.5,3));
	LoadedModel<> calculator("models/calculator/calculadora.obj", _lightProgram);
	TexturedObject calcTextured(calculator);
	calcTextured.useTexture("models/calculator/Calculadora_Color.png", TextureTypes::diffuse, 0, false);
	calcTextured.setScale(glm::vec3(0.2f)).setPosition(glm::vec3(-5, 0, 4));

	std::vector<std::unique_ptr<RenderableObject>> toRender;
	MaterialRenderable first_cube_with_material(texturedCube, MATERIALS::emerald);
	MaterialRenderable second_cube_with_material(texturedCube, MATERIALS::gold);
	MaterialRenderable floor_cube_with_material(texturedCube, MATERIALS::obsidian);
	toRender.push_back(std::make_unique<RenderableObject>(floor_cube_with_material, glm::vec3(0, -1.5f, 0), glm::vec3(40.0f, 0.1f, 40.0f)));
	toRender.push_back(std::make_unique<RenderableObject>(first_cube_with_material, glm::vec3(0, 0, 0)));
	toRender.push_back(std::make_unique<RenderableObject>(second_cube_with_material, glm::vec3(0, 0, 8)));
	toRender.push_back(std::make_unique<RenderableObject>(second_cube_with_material, glm::vec3(-9, 5, 9)));
	toRender.push_back(std::make_unique<RenderableObject>(second_cube_with_material, glm::vec3(-7, 4, 5)));
	toRender.push_back(std::make_unique<RenderableObject>(second_cube_with_material, glm::vec3(-5, 2, 2)));
	toRender.push_back(std::make_unique<RenderableObject>(second_cube_with_material, glm::vec3(7, 6, 7)));
	toRender.push_back(std::make_unique<RenderableObject>(second_cube_with_material, glm::vec3(-7, 3, -2)));
	toRender.push_back(std::make_unique<RenderableObject>(second_cube_with_material, glm::vec3(-9, 1, -4)));

	std::vector<LightObject> lights{
		LightObject(spot_light, light_model),
		LightObject(point_light, light_model),
		LightObject(direction_light),
	};
	lights[0].setScale(glm::vec3(0.2f)).setPosition(glm::vec3(1.5f, 2.0f, -3.0f));
	lights[1].setScale(glm::vec3(0.2f)).setPosition(glm::vec3(-7.0f, 1.0f, 5.0f));
	AmbientLight ambient(0.25f);
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
				if (e.key.keysym.scancode == SDL_SCANCODE_F6)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				if (e.key.keysym.scancode == SDL_SCANCODE_F7)
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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


		// compute transformations
		glm::mat4 projective = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 200.0f);
		glm::mat4 view = c->createTransformMatrix();

		// update lighting
		lights_wrapper.clear();
		for (LightObject& obj : lights) {
			lights_wrapper.addLight(obj);
		}

		// render light cube
		lights_wrapper.updateRendering(_lightProgram, *c, false);
		RenderableObject::transformations(_lightProgram, nullptr, &view, &projective);
		for (LightObject& obj : lights) {
			obj.render(_lightProgram);
		}

		// render imported
		ambient.use(_importedProgram);
		lights_wrapper.updateRendering(_importedProgram, *c);
		RenderableObject::transformations(_importedProgram, nullptr, &view, &projective);
		guitar_textured.render(_importedProgram);
		calcTextured.render(_importedProgram);

		// render objects
		ambient.use(_objectProgram);
		RenderableObject::transformations(_objectProgram, nullptr, &view, &projective);
		lights_wrapper.updateRendering(_objectProgram, *c);
		for (auto& obj : toRender) {
			//obj->render(_objectProgram);
		}

		// Swap the buffers
		SDL_GL_SwapWindow(_window);
	}
}
