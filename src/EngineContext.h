#ifndef _ENGINECONTEXT_H
#define _ENGINECONTEXT_H

#include <SDL2/SDL.h>

/** @brief The EngineContext struct contains the necessary SDL and OpenGL contexts for the engine. */
struct EngineContext {
    SDL_Window *window; /** The SDL window. */
    SDL_Renderer *renderer; /** The SDL renderer. */
    SDL_Event event; /** The SDL event. */
    SDL_GLContext gl_context; /** The OpenGL context. */

    /**
     * @brief Creates the EngineContext.
     * @param title The title of the window.
     * @param pos_x The x position of the window.
     * @param pos_y The y position of the window.
     * @param width The width of the window.
     * @param height The height of the window.
     * @param win_flags The flags for the SDL window.
     * @param rnd_flags The flags for the SDL renderer.
     * @return True if the contexts were created successfully, false otherwise.
     */
    bool create(const char *title, int pos_x, int pos_y, int width, int height, int win_flags, int rnd_flags);

    /** @brief Frees the SDL and OpenGL contexts. */
    void cleanup();

    /** @brief Destructor that calls cleanup(). */
    ~EngineContext() {cleanup();}
};

#endif//_ENGINECONTEXT_H