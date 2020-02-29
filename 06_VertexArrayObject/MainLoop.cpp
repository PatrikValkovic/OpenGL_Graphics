#include "MainLoop.h"
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
	RAII<GLuint> rotationBuffer([](GLuint b) {glDeleteBuffers(1, &b); }, GLuint(0));
	RAII<GLuint> elementBuffer([](GLuint b) {glDeleteBuffers(1, &b); }, GLuint(0));
	RAII<GLuint> rotaryAO([](GLuint a) { glDeleteVertexArrays(1, &a); }, GLuint(0));
	float rotation = 0;
	{
		// fill vertices
		float vertices[] = {
			 -0.5f, 0.5f, 0.0f,
			 0.0f, 0.5f, 0.0f,
			 -0.5f,  0.0f, 0.0f,
			  0.0f, 0.0f, 0.0f,
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
		// fill rotating angle
		glGenBuffers(1, &(rotationBuffer.getResource()));
		glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float), nullptr, GL_DYNAMIC_DRAW);
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); // setup shader attribute
		glEnableVertexAttribArray(0); // enable shader attribute

		glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer); // activate rotation buffer
		glVertexAttribDivisor(1, 3); // duplicate the rotation shader attribute three times
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr); // setup shader attribute
		glEnableVertexAttribArray(1); // enable shader attribue
		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind rotation buffer

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer); // use element buffer for rendering

		glBindVertexArray(0); // unbind VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind EBO - must be after unbind of VAO, otherwise is unbinded in VAO as well
	}

	// main loop
	SDL_Event e;
	bool keep_running = true;
	while (keep_running) {
		// handle events
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				keep_running = false;
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
		glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer); // bind buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float), &rotation); // copy new rotation for the shader
		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind buffer

		// render
		glBindVertexArray(rotaryAO); // bind VAO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // render
		glBindVertexArray(0); // unbind VAO

		// Swap the buffers
		SDL_GL_SwapWindow(_window);
	}
}
