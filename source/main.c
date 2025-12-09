#include <stdio.h>

#include "SDL.h"

int main(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL Initialization failed. ERROR: %s\n", SDL_GetError());
        return 1;
    }

    // Creating a window
    SDL_Window *window = SDL_CreateWindow("Window Test", 800, 600, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Window Creation failed. ERROR: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        printf("Renderer Creation failed. ERROR: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Event loop
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = 1;
        }

        // Set draw color to black and clear
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // R, G, B, A
        SDL_RenderClear(renderer);
        
        // Present the renderer (update the screen)
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
