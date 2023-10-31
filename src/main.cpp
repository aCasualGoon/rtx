#include <iostream>
#include "EngineContext.h"
#include "drawing.h"

using namespace std;

constexpr const char *WINDOW_TITLE = "Hello World!";
constexpr int WINDOW_POS_X   = 100;
constexpr int WINDOW_POS_Y   = 100;
constexpr int WINDOW_SIZE_W  = 640;
constexpr int WINDOW_SIZE_H  = 480;
constexpr int WINDOW_FLAGS   = SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL;
constexpr int RENDERER_FLAGS = SDL_RENDERER_ACCELERATED;

bool loop(EngineContext *context) {
    SDL_Event *event = &context->event;
    bool running = true;
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                running = false;
                break;
            case  SDL_WINDOWEVENT:
                if (event->window.event == SDL_WINDOWEVENT_RESIZED)
                    glViewport(0, 0, event->window.data1, event->window.data2);
                break;

            default:break;
        }
    }
    return running;
}

int main(int argc, char *argv[]) {
    // initialize SDL and OpenGL
    EngineContext context;
    if(!context.create(WINDOW_TITLE, WINDOW_POS_X,WINDOW_POS_Y, WINDOW_SIZE_W,WINDOW_SIZE_H, WINDOW_FLAGS, RENDERER_FLAGS))
        return 1;

    // main loop
    while(loop(&context)) {
        // draw(&context);
        Shader shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
        draw_shader(&context, &shader);
    }
}
