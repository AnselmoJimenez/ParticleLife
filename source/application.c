#include <stdio.h>

#include "SDL.h"
#include "SDL_video.h"
#include "glad/glad.h"

#include "../include/application.h"
#include "../include/particle.h"

#define DEFAULT_HEIGHT  800
#define DEFAULT_WIDTH   1800

// init_application : initializes the resources for the application
int init_application(application_t *application) {
    if (application->state != UNINITIALIZED) return 0;

    // Initialize SDL subsystems
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL Initialization failed. ERROR: %s\n", SDL_GetError());
        return 0;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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
    application->gl_context = SDL_GL_CreateContext(application->window);
    if (application->gl_context == NULL) {
        printf("OpenGL Context Creation failed. ERROR: %s\n", SDL_GetError());
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        return 0;
    }

    // Initialize GLAD with the function to load the address of OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        SDL_GL_DestroyContext(application->gl_context);
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        return 0;
    }

    // Set the OpenGL rendering window size
    glViewport(0, 0, application->width, application->height);
    
    // print OpenGL version
    printf("OpenGL %s\n", glGetString(GL_VERSION));

    application->state = RUNNING;

    return 1;
}

// destroy_application : destroys the allocated resources for the application
int destroy_application(application_t *application) {
    if (application->state != RUNNING || application->state != PAUSED) return 0;

    // Destroy Open GL Context
    if (application->gl_context)
        SDL_GL_DestroyContext(application->gl_context);

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
static void handle_events(application_t *application) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_EVENT_QUIT: {
                application->state = UNINITIALIZED;
                break;
            }
            case SDL_EVENT_WINDOW_RESIZED: {
                SDL_GetWindowSize(application->window, &application->width, &application->height);
                glViewport(0, 0, application->width, application->height);
                break;
            }
            case SDL_EVENT_MOUSE_MOTION:
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP:
                break; 
            default: break;
        }
    }
}

// mainloop : the application main loop
int mainloop(application_t *application) {
    // particle_t *particles = init_particles(application, NUMPARTICLES, MAXNUMCLASSES);

    while (application->state == RUNNING || application->state == PAUSED) {
        handle_events(application);

        // Set draw color to black and clear 
        glClearColor(RGBA_BLACK);
        glClear(GL_COLOR_BUFFER_BIT);
        // Draw particles on the screen
        // for (int i = 0; i < NUMPARTICLES; i++)
            // draw_particle(application, particles[i]);
        
        // Present the renderer (update the screen)
        SDL_GL_SwapWindow(application->window);

        // update_particles(application, particles);
    }

    // destroy_particles(particles);

    return 1;
}