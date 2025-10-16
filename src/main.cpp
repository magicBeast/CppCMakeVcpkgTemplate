#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include <SDL3/SDL.h>
#include <imgui.h>

int main(int argc, char *argv[])
{
    // Initialize SDL3
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        return -1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("SDL3 + imgui Test", 800, 600, SDL_WINDOW_RESIZABLE);

    // Create renderer (uses Metal on macOS!)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

    // Setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    // Setup imgui backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    bool running = true;
    while (running)
    {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        // Start imgui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // ImGui window
        ImGui::Begin("Test Window");
        ImGui::Text("Hello from SDL3 + imgui!");
        ImGui::Text("FPS: %.1f", io.Framerate);
        if (ImGui::Button("Quit"))
        {
            running = false;
        }
        ImGui::End();

        // Render
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
        SDL_RenderClear(renderer);

        // Draw a test rectangle
        SDL_FRect rect = {350, 250, 100, 100};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        // Render imgui
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
