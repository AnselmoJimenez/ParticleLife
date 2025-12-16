#include <stdio.h>

#include "SDL.h"

#include "../include/application.h"

int main(void) {
    application_t application = { 0 };
    init_application(&application);

    // Event loop
    while (application.running) {
        handle_events(&application);

        // Set draw color to black and clear
        SDL_SetRenderDrawColor(application.renderer, 0, 0, 0, 255);  // R, G, B, A
        SDL_RenderClear(application.renderer);
        
        // Present the renderer (update the screen)
        SDL_RenderPresent(application.renderer);
    }

    // Clean up
    destroy_application(&application);

    return 0;
}
