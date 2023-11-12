#ifndef _EDITOR_H
#define _EDITOR_H

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../EngineContext.h"
#include "../Camera.h"

/**
 * @brief Class to handle the Editor interactions.
 * The Editor uses the Dear ImGui library to create its UI.
*/
class Editor {
public:
    Editor(EngineContext& context)
    : engineContext(context) {
        InitImGui();
    }

    ~Editor() {
        // Cleanup ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void Tick() {
        HandleEvents();
        RenderGui();
    }

private:
    EngineContext& engineContext;

    void InitImGui() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Setup Platform/Renderer bindings
        ImGui_ImplSDL2_InitForOpenGL(engineContext.window, engineContext.gl_context);
        ImGui_ImplOpenGL3_Init("#version 130"); // Adjust the GLSL version as needed
    }

    void HandleEvents() {
        while (SDL_PollEvent(&engineContext.event)) {
            // Pass events to ImGui
            ImGui_ImplSDL2_ProcessEvent(&engineContext.event);
        }
    }

    void RenderGui() {
        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(engineContext.window);
        ImGui::NewFrame();

        // Define your GUI here
        BuildGui();

        // Rendering
        ImGui::Render();
        SDL_GL_MakeCurrent(engineContext.window, engineContext.gl_context);
        glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f); // Clear color
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(engineContext.window);
    }

    void BuildGui() {
        // Build your GUI here
        ImGui::Begin("Editor Window");
        // Add GUI elements like buttons, sliders, etc.
        ImGui::End();
    }
};

#endif//_EDITOR_H