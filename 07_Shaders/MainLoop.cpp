#include "MainLoop.h"
#include <chrono>
#include <iostream>
#include "ShadersSupport.h"

MainLoop::MainLoop(SDL_Window* win) : _window(win)
{}

void MainLoop::compile_program()
{
	// compile shaders
	RAII<GLuint> vertexShader(glDeleteShader, compile_shader, "vs.vert", GL_VERTEX_SHADER);
	RAII<GLuint> fragmentShader(glDeleteShader, compile_shader, "fs.frag", GL_FRAGMENT_SHADER);
	RAII<GLuint> vertexShader2(glDeleteShader, compile_shader, "learngl.vert", GL_VERTEX_SHADER);
	RAII<GLuint> fragmentShader2(glDeleteShader, compile_shader, "learngl.frag", GL_FRAGMENT_SHADER);

	// create program
	_program = RAII<GLuint>(glDeleteProgram, glCreateProgram);
	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragmentShader);
	link_program(_program);

	_program2 = RAII<GLuint>(glDeleteProgram, glCreateProgram);
	glAttachShader(_program2, vertexShader2);
	glAttachShader(_program2, fragmentShader2);
	link_program(_program2);
}

void MainLoop::loop()
{
	// create vertex buffer
	RAII<GLuint> vertexBuffer([](GLuint b) {glDeleteBuffers(1, &b); }, GLuint(0));
	RAII<GLuint> elementBuffer([](GLuint b) {glDeleteBuffers(1, &b); }, GLuint(0));
	RAII<GLuint> rotaryAO([](GLuint a) { glDeleteVertexArrays(1, &a); }, GLuint(0));
	float rotation = 0;
	{
		// fill vertices
		float vertices[] = {
			// positions			// colors
			 -0.5f, 0.5f, 0.0f,		1.0,0.0,0.0,
			 0.0f, 0.5f, 0.0f,		0.0,1.0,0.0,
			 -0.5f,  0.0f, 0.0f,	0.0,0.0,1.0,
			  0.0f, 0.0f, 0.0f,		1.0,1.0,1.0,
		};
		// vertices order
		unsigned int indices[] = {
			0, 1, 2, // top left triangle
			1, 2, 3, // bottom right triangle
		};
		glGenBuffers(1, &(vertexBuffer.getResource()));
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// fill element buffer
		glGenBuffers(1, &(elementBuffer.getResource()));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// create AO
		glGenVertexArrays(1, &(rotaryAO.getResource()));
		glBindVertexArray(rotaryAO); // bind VAO
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // active vertex buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr); // setup shader attribute
		glEnableVertexAttribArray(0); // enable shader attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer); // use element buffer for rendering

		glBindVertexArray(0); // unbind VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind EBO - must be after unbind of VAO, otherwise is unbinded in VAO as well
	}

	// get reference to the uniform variable
	GLint rotationPosition = glGetUniformLocation(_program2, "rotation");
	if (rotationPosition == -1) {
		std::cerr << "rotation uniform variable not found" << std::endl;
	}
	GLint colorPosition = glGetUniformLocation(_program2, "unifColor");
	if (colorPosition == -1) {
		std::cerr << "unifColor uniform variable not found" << std::endl;
	}

	// for FPS counting
	std::chrono::system_clock::time_point last_print = std::chrono::system_clock::now();
	int frames = 0;

	// main loop
	SDL_Event e;
	bool keep_running = true;
	while (keep_running) {
		// handle events
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				keep_running = false;
		}

		// measure FPS
		frames++;
		if (last_print + std::chrono::seconds(1) < std::chrono::system_clock::now()) {
			std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			last_print = std::chrono::system_clock::now();
		}

		// Set up viewport
		int w, h;
		SDL_GetWindowSize(_window, &w, &h);
		glViewport(0, 0, w, h);
		glUseProgram(0);

		// Clear the screen
		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// first program
		glUseProgram(_program);
		glPointSize(10.0f);
		glDrawArrays(GL_LINE_STRIP, 0, 8);

		// second program
		glUseProgram(_program2);

		// compute new rotation
		rotation += 1; // compute new rotation
		if (rotation > 360) rotation -= 360;
		glUniform1f(rotationPosition, rotation); // set up the uniform variable

		// render
		glBindVertexArray(rotaryAO); // bind VAO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // render
		glBindVertexArray(0); // unbind VAO

		// Swap the buffers
		SDL_GL_SwapWindow(_window);
	}
}
