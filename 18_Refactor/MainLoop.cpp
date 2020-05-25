#include "MainLoop.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <SDL_image.h>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include "ShadersSupport.h"
#include "SDLsupport.h"
#include "FPSCounter.h"
#include "CubeModel.h"
#include "SimCamera.h"
#include "FlyCamera.h"
#include "AmbientLight.h"
#include "LightsWrapper.h"
#include "Materials.h"
#include "MaterialRenderable.h"
#include "TextureRenderable.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Spotlight.h"
#include "ModelObject.h"
#include "TexturedObject.h"
#include "MirrorPaneModel.h"

MainLoop::MainLoop(SDL_Window* win) : _window(win)
{}

void MainLoop::compile_program()
{
	// compile transformation program
	{
		RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "compiledshaders/white.vert", GL_VERTEX_SHADER);
		RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "compiledshaders/white.frag", GL_FRAGMENT_SHADER);
		_whiteProgram = RAII<GLuint>(glDeleteProgram, glCreateProgram);
		glAttachShader(_whiteProgram, vertexShader);
		glAttachShader(_whiteProgram, fragmentShader);
		link_program(_whiteProgram);
	}

	// compile main program with lights
	{
		RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "compiledshaders/main.vert", GL_VERTEX_SHADER);
		RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "compiledshaders/main.frag", GL_FRAGMENT_SHADER);
		_mainProgram = RAII<GLuint>(glDeleteProgram, glCreateProgram);
		glAttachShader(_mainProgram, vertexShader);
		glAttachShader(_mainProgram, fragmentShader);
		link_program(_mainProgram);
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
	std::unique_ptr<BaseCamera> camera = std::make_unique<FlyCamera>(glm::vec3(0, 1, 0), glm::vec3(1, 1, 2));
	// lights
	CubeModel light_model;
	RenderableObject light_object(&light_model, glm::vec3(0), glm::vec3(0.1f));
	Spotlight spot_light(5.0f, 10.0f, glm::vec3(-1, -1, 4));
	PointLight point_light(glm::vec3(1.0, 0.14, 0.07), 2.0f);
	DirectionalLight direction_light(glm::vec3(1.0, -5.0, -2.0), glm::vec3(1.0, 1.0, 1.0), 1.0f);
	// cube
	CubeModel cube_model;
	RenderableObject cube_object(&cube_model);
	TexturedObject cube_textured(&cube_object);
	cube_textured.useTexture("textures/container.png", TextureTypes::diffuse, 0);
	cube_textured.useTexture("textures/container_specular.png", TextureTypes::specular, 0);
	// guitar
	ModelObject guitar("models/SurvivalBackPack/Survival_BackPack_2.fbx");
	TexturedObject guitar_textured(&guitar);
	guitar_textured
		.useTexture("models/SurvivalBackPack/1001_albedo.jpg", TextureTypes::diffuse, 0, false)
		.useTexture("models/SurvivalBackPack/1001_AO.jpg", TextureTypes::ambient_occlusion, 0, false)
		.useTexture("models/SurvivalBackPack/1001_metallic.jpg", TextureTypes::specular, 0, false)
		.useTexture("models/SurvivalBackPack/1001_normal.png", TextureTypes::normal, 0, false)
		.useTexture("models/SurvivalBackPack/1001_roughness.jpg", TextureTypes::rougness, 0, false);
	guitar_textured.setScale(glm::vec3(0.004f))
				  .setPosition(glm::vec3(-0.5,1.5,3));
	// calculator
	ModelObject calculator("models/calculator/calculadora.obj");
	TexturedObject calcTextured(&calculator);
	calcTextured.useTexture("models/calculator/Calculadora_Color.png", TextureTypes::diffuse, 0, false);
	calcTextured.setScale(glm::vec3(0.2f)).setPosition(glm::vec3(-5, 0, 4));
	// penguin
	ModelObject penguin("models/penguin/PenguinBaseMesh.fbx");
	TexturedObject penguinTextured(&penguin);
	penguinTextured.useTexture("models/penguin/Penguin Diffuse Color.png", TextureTypes::diffuse, 0, false)
		.setScale(glm::vec3(0.01f))
		.setPosition(glm::vec3(3, 1, -4));
	// iron man
	ModelObject ironman("models/IronManMark/Iron_Man_Mark_44_Hulkbuster_fbx.fbx");
	ironman.setScale(glm::vec3(0.01f)).setPosition(glm::vec3(3, 1, 5));
	// plant
	ModelObject plant("models/plant/indoor plant_02_+2.fbx");
	TexturedObject plant_textured(&plant);
	plant_textured.useTexture("models/plant/indoor plant_2_COL.jpg", TextureTypes::diffuse, 0, false);
	plant_textured.useTexture("models/plant/indoor plant_2_NOR.jpg", TextureTypes::normal, 0, false);
	plant_textured
		.setScale(glm::vec3(0.001f))
		.setPosition(glm::vec3(-4, 1, 8));
	// mirror
	ModelObject mirror("models/mirror/Baker_Emerald_Mirror.obj");
	MirrorPaneModel mirror_pane;
	RenderableObject mirror_pane_renderable(&mirror_pane);
	TexturedObject mirror_pane_textured(&mirror_pane_renderable);
	TexturedObject mirror_textured(&mirror);
	mirror_textured.useTexture("models/mirror/dcmap_Baker_Emerald Mirror_diff.jpg", TextureTypes::diffuse, 0, false);
	mirror_textured
		.setRotation(glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)))
		.setScale(glm::vec3(0.01f))
		.setPosition(glm::vec3(7, 0, 0));
	mirror_pane_textured
		.setRotation(glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)))
		.setScale(glm::vec3(0.01f))
		.setPosition(glm::vec3(7, 0, 0) + glm::vec3(0.0f, 0.0f, -1.81f) * 0.01f);

	std::vector<std::unique_ptr<WrapObject>> toRender;
	toRender.push_back(std::make_unique<WrapObject>(&cube_textured, glm::vec3(0, -1.5f, 0), glm::vec3(40.0f, 0.1f, 40.0f)));
	toRender.push_back(std::make_unique<WrapObject>(&cube_textured, glm::vec3(0, 0, 0)));
	toRender.push_back(std::make_unique<WrapObject>(&cube_textured, glm::vec3(0, 0, 8)));
	toRender.push_back(std::make_unique<WrapObject>(&cube_textured, glm::vec3(-9, 5, 9)));
	toRender.push_back(std::make_unique<WrapObject>(&cube_textured, glm::vec3(-7, 4, 5)));
	toRender.push_back(std::make_unique<WrapObject>(&cube_textured, glm::vec3(-5, 2, 2)));
	toRender.push_back(std::make_unique<WrapObject>(&cube_textured, glm::vec3(7, 6, 7)));
	toRender.push_back(std::make_unique<WrapObject>(&cube_textured, glm::vec3(-7, 3, -2)));
	toRender.push_back(std::make_unique<WrapObject>(&cube_textured, glm::vec3(-9, 1, -4)));

	std::vector<LightObject> lights{
		LightObject(spot_light),
		LightObject(point_light),
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
				camera->lookUp((float)e.motion.yrel * mouse_sensitivity);
				camera->lookRight((float)e.motion.xrel * mouse_sensitivity);
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
					camera = std::make_unique<FlyCamera>(glm::vec3(0, 1, 0), camera->getPos(), camera->getViewDirection());
				if (e.key.keysym.scancode == SDL_SCANCODE_F10)
					camera = std::make_unique<SimCamera>(camera->getPos(), camera->getViewDirection(), camera->getCameraUp());
			}
		}
		Uint8 const* keyboard_state = SDL_GetKeyboardState(nullptr);
		if (keyboard_state[SDL_SCANCODE_W]) camera->moveZ(delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_S]) camera->moveZ(-delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_A]) camera->moveX(-delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_D]) camera->moveX(delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_R]) camera->moveY(delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_F]) camera->moveY(-delta_time * movement_speed);
		if (keyboard_state[SDL_SCANCODE_E]) camera->rotateRight(delta_time * rotation_speed);
		if (keyboard_state[SDL_SCANCODE_Q]) camera->rotateLeft(-delta_time * rotation_speed);

		// Set up viewport
		int w, h;
		SDL_GetWindowSize(_window, &w, &h);
		glViewport(0, 0, w, h);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// compute transformations
		glm::mat4 projective = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 200.0f);
		glm::mat4 view = camera->createTransformMatrix();

		// update lighting
		lights_wrapper.clear();
		for (LightObject& obj : lights) {
			lights_wrapper.addLight(&obj);
		}


		// fill depth buffer - TODO is to worth it?
		/*
		glDepthFunc(GL_LESS);
		lights_wrapper.updateRendering(_whiteProgram, *camera, false);
		BaseObject::transformations(_whiteProgram, nullptr, &view, &projective);
		for (LightObject& obj : lights) {
			light_object.setPosition(obj.getPosition());
			light_object.render(_whiteProgram);
		}
		guitar_textured.render(_whiteProgram);
		calcTextured.render(_whiteProgram);
		for (auto& obj : toRender) { // render cubes
			obj->render(_whiteProgram);
		}
		glDepthFunc(GL_EQUAL);
		*/


		// render light cube
		BaseObject::transformations(_whiteProgram, nullptr, &view, &projective);
		for (LightObject& obj : lights) {
			light_object.setPosition(obj.getPosition());
			light_object.render(_whiteProgram);
		}

		// render imported
		ambient.use(_mainProgram);
		lights_wrapper.updateRendering(_mainProgram, *camera);
		RenderableObject::transformations(_mainProgram, nullptr, &view, &projective);
		guitar_textured.render(_mainProgram);
		calcTextured.render(_mainProgram);
		penguinTextured.render(_mainProgram);
		ironman.render(_mainProgram);
		plant_textured.render(_mainProgram);
		mirror_textured.render(_mainProgram);
		mirror_pane_textured.render(_whiteProgram);
		for (auto& obj : toRender) { // render cubes
			obj->render(_mainProgram);
		}

		// Swap the buffers
		SDL_GL_SwapWindow(_window);
	}
}
