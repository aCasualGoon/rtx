#include "EngineContext.h"
#include "Shader.h"
#include "Camera.h"
#include <memory>
#include <list>
#include <SDL2/SDL.h>
using std::unique_ptr, std::make_unique, std::move;

constexpr const char *WINDOW_TITLE = "Shaded Window. Exciting stuff!";
constexpr int WINDOW_POS_X   = 100;
constexpr int WINDOW_POS_Y   = 100;
constexpr int WINDOW_SIZE_W  = 640;
constexpr int WINDOW_SIZE_H  = 480;
constexpr int WINDOW_FLAGS   = SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL;
constexpr int RENDERER_FLAGS = SDL_RENDERER_ACCELERATED;

constexpr const char *SHADER_SOURCE_VERTEX   = "src/shaders/vertex.glsl";
constexpr const char *SHADER_SOURCE_FRAGMENT = "src/shaders/fragment.glsl";

EngineContext context;
Shader shader;
Camera camera;
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

const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
#define isKeyDown(KEY) keyboard_state[KEY]
#define getAxis(KEYLOW,KEYHIGH) (keyboard_state[KEYHIGH] - keyboard_state[KEYLOW])
bool loop(EngineContext *context, float delta_time) {
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
            
            // case SDL_MOUSEMOTION:
            //     camera.rotate_by_clamped(event->motion.yrel * 0.1, event->motion.xrel * 0.1);
            //     break;

            default:break;
        }

    }

    if(isKeyDown(SDL_SCANCODE_ESCAPE))
        running = false;

    GLfloat dpitch = -getAxis(SDL_SCANCODE_DOWN,SDL_SCANCODE_UP) * 0.1;
    GLfloat dyaw = getAxis(SDL_SCANCODE_LEFT,SDL_SCANCODE_RIGHT) * 0.1;
    if(dpitch != 0 || dyaw != 0)
        camera.rotate_by_clamped(dpitch,dyaw);

    int8_t dx = getAxis(SDL_SCANCODE_A,SDL_SCANCODE_D);
    int8_t dy = getAxis(SDL_SCANCODE_LSHIFT,SDL_SCANCODE_SPACE);
    int8_t dz = getAxis(SDL_SCANCODE_S,SDL_SCANCODE_W);
    vec3 dmove = vec3(dx,dy,dz);
    if(length(dmove) > 1)
        dmove = normalize(dmove);
    camera.move_by_local(dmove * 0.005f);

    return running;
}

int main(int argc, char *argv[]) {
    init_result inited = init();
    if (!inited.success) return 1;

    context = *inited.context_ptr;
    camera = *inited.camera_ptr;

    uint64 last_frame_time = SDL_GetTicks64();

    bool running = true;
    while(running) {
        float current_frame_time = SDL_GetTicks64();
        running = loop(&context, current_frame_time - last_frame_time);
        camera.render();
        last_frame_time = current_frame_time;
    }
}
