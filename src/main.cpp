#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::move;
#include "EngineContext.h"
#include "Shader.h"
#include "Camera.h"
#include "editor/Editor.h"

constexpr const char *WINDOW_TITLE = "Shaded Window. Exciting stuff!";
constexpr int WINDOW_POS_X   = 100;
constexpr int WINDOW_POS_Y   = 100;
constexpr int WINDOW_SIZE_W  = 640;
constexpr int WINDOW_SIZE_H  = 480;
constexpr int WINDOW_FLAGS   = SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL;
constexpr int RENDERER_FLAGS = SDL_RENDERER_ACCELERATED;

constexpr const char *SHADER_SOURCE_VERTEX   = "src/shaders/vertex.glsl";
constexpr const char *SHADER_SOURCE_FRAGMENT = "src/shaders/fragment.glsl";

struct init_result { 
    bool success;
    unique_ptr<EngineContext> context_ptr;
    unique_ptr<Shader> shader_ptr;
    unique_ptr<Camera> camera_ptr;
};
init_result init() {
    // initialize EngineContext
    unique_ptr<EngineContext> context_ptr = make_unique<EngineContext>();
    if(!context_ptr->create(WINDOW_TITLE, WINDOW_POS_X,WINDOW_POS_Y, WINDOW_SIZE_W,WINDOW_SIZE_H, WINDOW_FLAGS, RENDERER_FLAGS))
        return {false, nullptr, nullptr, nullptr};

    // initialize shader
    unique_ptr<Shader> shader_ptr = make_unique<Shader>();
    if(!shader_ptr->create(SHADER_SOURCE_VERTEX,SHADER_SOURCE_FRAGMENT))
        return {false, nullptr, nullptr, nullptr};

    unique_ptr<Camera> camera_ptr = make_unique<Camera>(context_ptr.get(), shader_ptr.get());

    return {true, move(context_ptr), move(shader_ptr), move(camera_ptr)};
}

bool loop(EngineContext *context) {
    SDL_Event *event = &context->event;
    bool running = true;
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                if (event->window.event == SDL_WINDOWEVENT_RESIZED)
                    glViewport(0, 0, event->window.data1, event->window.data2);
                break;

            default:break;
        }
    }
    return running;
}

int main(int argc, char *argv[]) {
    init_result inited = init();
    if (!inited.success) return 1;

    EngineContext& context = *inited.context_ptr;
    Shader& shader = *inited.shader_ptr;
    Camera& camera = *inited.camera_ptr;

    Editor editor(context);

    while(loop(&context)) {
        camera.render();
        editor.Tick();
    }
}
