#include <stdio.h>

#include "SDL.h"
#include "SDL_video.h"

#include "../include/application.h"
#include "../include/particle.h"

#define DEFAULT_HEIGHT  600
#define DEFAULT_WIDTH   800

// init_application : initializes the resources for the application
int init_application(application_t *application) {
    if (application->state != UNINITIALIZED) return 0;

    // Initialize SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL Initialization failed. ERROR: %s\n", SDL_GetError());
        return 0;
    }
    application->state = RUNNING;

    application->height = DEFAULT_HEIGHT;
    application->width = DEFAULT_WIDTH;

    // initialize the window
    application->window = SDL_CreateWindow("Particle Life", DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_OPENGL);
    if (application->window == NULL) {
        printf("Window Creation failed. ERROR: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    if (!SDL_SetWindowResizable(application->window, true)) {
        printf("Unable to set window resizable. ERROR: %s\n", SDL_GetError());
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        return 0;
    }

    // Initialize the renderer
    application->renderer = SDL_CreateRenderer(application->window, NULL);
    if (application->renderer == NULL) {
        printf("Renderer Creation failed. ERROR: %s\n", SDL_GetError());
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

// destroy_application : destroys the allocated resources for the application
int destroy_application(application_t *application) {
    if (application->state != RUNNING || application->state != PAUSED) return 0;

    // Destroy Renderer
    if (application->renderer) {
        SDL_DestroyRenderer(application->renderer);
        application->renderer = NULL;
    }

    // Destroy Window
    if (application->window) {
        SDL_DestroyWindow(application->window);
        application->window = NULL;
    }
    
    // Quit subsystems
    SDL_Quit();

    return 1;
}


// handle_events : the event loop - checks for events and returns them
static SDL_EventType handle_events(application_t *application) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_EVENT_QUIT: 
                application->state = UNINITIALIZED;
                return SDL_EVENT_QUIT;
        
            case SDL_EVENT_WINDOW_RESIZED:
                SDL_GetWindowSize(application->window, &application->width, &application->height);
                return SDL_EVENT_WINDOW_RESIZED;

            default:
                return e.type;
        }
    }
    
    return SDL_EVENT_FIRST;
}

// mainloop : the application main loop
int mainloop(application_t *application) {
    particle_t particle = new_particle((vector2D_t) { (int) (application->width / 2), (int) (application->height / 2) }, RED);

    while (application->state == RUNNING || application->state == PAUSED) {
        handle_events(application);

        // Set draw color to black and clear
        SDL_SetRenderDrawColor(application->renderer, RGBA_BLACK);  // R, G, B, A
        SDL_RenderClear(application->renderer);

        // Present the renderer (update the screen)
        draw_particle(application, particle);

        // Present the renderer (update the screen)
        SDL_RenderPresent(application->renderer);
    }

    return 1;
}