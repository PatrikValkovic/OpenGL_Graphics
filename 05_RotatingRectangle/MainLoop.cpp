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
	float rotation = 0;
	{
		float vertices[] = {
			 -0.9f, 0.9f, 0.0f,
			 0.0f, 0.9f, 0.0f,
			 -0.9f,  0.0f, 0.0f
		};
		glGenBuffers(1, &(vertexBuffer.getResource()));
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glGenBuffers(1, &(rotationBuffer.getResource()));
		glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
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

		// bind so the data are taken from this buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		//which argument (specified by layout) to bind, size of the single vertex element (3 coordinates),
		//data type of data, if to normalize, 
		//"stride" = how far are vertex data from eatch other (we have 3 floats and they follow each other),
		//beginning of the data in the buffer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		// rotation
		glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer); // activate rotation buffer
		rotation += 1; // compute new rotation
		if (rotation > 360) rotation -= 360;
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float), &rotation); // copy new rotation for the shader
		glVertexAttribDivisor(1, 3); // duplicate the rotation shader attribute three times
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr); // setup shader attribute
		glEnableVertexAttribArray(1); // enable shader attribue
		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind rotation buffer
		//draw
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap the buffers
		SDL_GL_SwapWindow(_window);
	}
}
