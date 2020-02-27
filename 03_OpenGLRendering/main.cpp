#include <iostream>
#include <thread>
#include <chrono>
#include <SDL.h>
#include <glad.h>
#include "ShadersSupport.h"


int main(int argc, char** args)
{
    // load everything
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("03 / OpenGL Rendering",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    gladLoadGL();
    
    // compile shaders
    GLuint vshader = compile_shader("vs.vert", GL_VERTEX_SHADER);
    GLuint fshader = compile_shader("fs.frag", GL_FRAGMENT_SHADER);

    // create program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vshader);
    glAttachShader(shaderProgram, fshader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vshader);
    glDeleteShader(fshader);

    // create geometry
    GLuint vertexArrayObject = 0;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL we'd like to use the previously compiled shader program
        glUseProgram(shaderProgram);
        // Draw the scene geometry - just tell OpenGL we're drawing at this point
        glPointSize(10.0f);
        glDrawArrays(GL_POINTS, 0, 1);
        // Unbind the shader program
        glUseProgram(0);

        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteProgram(shaderProgram);
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}