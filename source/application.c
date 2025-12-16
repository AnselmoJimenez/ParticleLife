#include <stdio.h>

#include "SDL.h"

#include "../include/application.h"

#define HEIGHT  600
#define WIDTH   800

// init_application : initializes the resources for the application
int init_application(application_t *application) {
    // Initialize SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL Initialization failed. ERROR: %s\n", SDL_GetError());
        return 1;
    }
    application->running = true;

    application->height = HEIGHT;
    application->width = WIDTH;

    // initialize the window
    application->window = SDL_CreateWindow("Particle Life", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (application->window == NULL) {
        printf("Window Creation failed. ERROR: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Initialize the renderer
    application->renderer = SDL_CreateRenderer(application->window, NULL);
    if (application->renderer == NULL) {
        printf("Renderer Creation failed. ERROR: %s\n", SDL_GetError());
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        return 1;
    }

    return 0;
}

// destroy_application : destroys the allocated resources for the application
int destroy_application(application_t *application) {
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

    return 0;
}

// handle_events : checks for events and returns them
SDL_EventType handle_events(application_t *application) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_EVENT_QUIT: 
                application->running = false;
                return SDL_EVENT_QUIT;
        }
    }
    
    return SDL_EVENT_FIRST;
}