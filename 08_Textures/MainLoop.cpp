#include "MainLoop.h"
#include <chrono>
#include <iostream>
#include <SDL_image.h>
#include "ShadersSupport.h"
#include "SDLsupport.h"

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
	// create vertex buffer
	RAII<GLuint> vertexBuffer([](GLuint b) {glDeleteBuffers(1, &b); }, GLuint(0));
	RAII<GLuint> elementBuffer([](GLuint b) {glDeleteBuffers(1, &b); }, GLuint(0));
	RAII<GLuint> rotaryAO([](GLuint a) { glDeleteVertexArrays(1, &a); }, GLuint(0));
	RAII<GLuint> texture([](GLuint t) {glDeleteTextures(1, &t); }, GLuint(0));
	RAII<GLuint> secondTexture([](GLuint t) {glDeleteTextures(1, &t); }, GLuint(0));
	float rotation = 0;
	{
		// fill vertices
		float vertices[] = {
			// positions			// colors		// texture coords
			 -0.5f, 0.5f, 0.0f,		1.0,0.0,0.0,	0.0f, 1.0f,
			 0.0f, 0.5f, 0.0f,		0.0,1.0,0.0,	1.0f, 1.0f,
			 -0.5f,  0.0f, 0.0f,	0.0,0.0,1.0,	0.0f, 0.0f,
			  0.0f, 0.0f, 0.0f,		1.0,1.0,1.0,	1.0f, 0.0f,
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr); // setup shader attribute
		glEnableVertexAttribArray(0); // enable shader attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer); // use element buffer for rendering

		glBindVertexArray(0); // unbind VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind EBO - must be after unbind of VAO, otherwise is unbinded in VAO as well

		RAII<SDL_Surface*> imgSurface(SDL_FreeSurface, IMG_Load, "wall.jpg");
		if (!imgSurface) {
			std::cerr << IMG_GetError() << std::endl;
			throw LoadException("Can't load image wall.jpg");
		}
		glGenTextures(1, &(texture.getResource()));
		glBindTexture(GL_TEXTURE_2D, texture);
		glad_glTexImage2D( // generates the texture
			GL_TEXTURE_2D, // texture target
			0, //mipmap level
			GL_RGB, // format in which we want to STORE texture
			imgSurface->w, // texture width
			imgSurface->h, // texture height
			0, //always 0, some legacy shit
			GL_RGB , // format of the SOURCE picture
			GL_UNSIGNED_BYTE, // datatype of the SOURCE image
			imgSurface->pixels // data
		);
		//glGenerateMipmap(GL_TEXTURE_2D); // use mitmaps
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //repeat texture over x axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); // clamp texture over y axis
		float borderColor[] = { 0.0f,0.0f,1.0f,1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); // set border color of clamped axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // use nearest algorithm when minimazing
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // use linear algorithm when magnifying the texture
		glBindTexture(GL_TEXTURE_2D, 0);

		RAII<SDL_Surface*> secSurface(SDL_FreeSurface, IMG_Load, "awesomeface.png");
 		if (!secSurface) {
			std::cerr << IMG_GetError() << std::endl;
			throw LoadException("Can't load image awesomeface.png");
		}
		glGenTextures(1, &(secondTexture.getResource()));
		glBindTexture(GL_TEXTURE_2D, secondTexture);
		glad_glTexImage2D( // generates the texture
			GL_TEXTURE_2D, // texture target
			0, //mipmap level
			GL_RGBA, // format in which we want to STORE texture, uses alpha this time
			secSurface->w, // texture width
			secSurface->h, // texture height
			0, //always 0, some legacy shit
			GL_RGBA, // format of the SOURCE picture, uses alpha this time
			GL_UNSIGNED_BYTE, // datatype of the SOURCE image
			secSurface->pixels // data
		);
		//glGenerateMipmap(GL_TEXTURE_2D); // use mitmaps
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //repeat texture over x axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); // clamp texture over y axis
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); // set border color of clamped axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // use nearest algorithm when minimazing
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // use linear algorithm when magnifying the texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// get reference to the uniform variable
	GLint rotationPosition = glGetUniformLocation(_program, "rotation");
	if (rotationPosition == -1) {
		std::cerr << "rotation uniform variable not found" << std::endl;
	}
	GLint colorPosition = glGetUniformLocation(_program, "unifColor");
	if (colorPosition == -1) {
		std::cerr << "unifColor uniform variable not found" << std::endl;
	}
	// this is not necessary as the sampler is automatically bind to the active texture with corresponding size
	// however might not happend, so its better to use it
	GLint texturePosition = glGetUniformLocation(_program, "texSampler");
	if (texturePosition == -1) {
		std::cerr << "texSampler uniform variable not found" << std::endl;
	}
	// get the second texture sampler position, this time needed because we want to use two textures
	GLint secondTexturePosition = glGetUniformLocation(_program, "secSampler");
	if (secondTexturePosition == -1) {
		std::cerr << "secSampler uniform variable not found" << std::endl;
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

		// Clear the screen
		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use program
		glUseProgram(_program);

		// compute new rotation
		rotation += 1; // compute new rotation
		if (rotation > 360) rotation -= 360;
		//glUniform1f(rotationPosition, rotation); // set up the uniform variable
		glUniform1i(texturePosition, 0); // set texture as GL_TEXTURE0
		glUniform1i(secondTexturePosition, 7); // set second texture as GL_TEXTURE7
		// texture binding can be possible moved out of the loop, we may change texture by using different texture units and their bindings

		// render
		glActiveTexture(GL_TEXTURE0); // activate the texture unit 0
		glBindTexture(GL_TEXTURE_2D, texture); // bind texture to unit 0
		glActiveTexture(GL_TEXTURE7); // activate the texture unit 7
		glBindTexture(GL_TEXTURE_2D, secondTexture); // bind texture to unit 7
		glBindVertexArray(rotaryAO); // bind VAO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // render
		glBindVertexArray(0); // unbind VAO
		glBindTexture(GL_TEXTURE_2D, 0); // unbind texture

		// Swap the buffers
		SDL_GL_SwapWindow(_window);
	}
}
