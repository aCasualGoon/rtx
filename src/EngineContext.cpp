#include "EngineContext.h"
#include <iostream>

bool EngineContext::create(const char *title, int pos_x, int pos_y, int width, int height, int win_flags, int rnd_flags)
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // create window and check for errors
    window = SDL_CreateWindow(title, pos_x, pos_y, width, height, win_flags);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        cleanup();
        SDL_Quit();
        return false;
    }

    // create renderer and check for errors
    renderer = SDL_CreateRenderer(window, -1, rnd_flags);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        cleanup();
        SDL_Quit();
        return false;
    }

    // create OpenGL context and check for errors
    gl_context = SDL_GL_CreateContext(window);
    if (gl_context == nullptr) {
        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
        cleanup();
        SDL_Quit();
        return false;
    }

    // initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cerr << "Error initializing GLEW! " << glewGetErrorString(glewError) << std::endl;
        cleanup();
        SDL_Quit();
        return false;
    }

    return true;
}

EngineContext::~EngineContext() { cleanup(); }

void EngineContext::cleanup()
{
    if(renderer != nullptr)
        SDL_DestroyRenderer(renderer);
    if(window != nullptr)
        SDL_DestroyWindow(window);
    if(gl_context != nullptr)
        SDL_GL_DeleteContext(gl_context);
    SDL_Quit();
}