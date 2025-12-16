#ifndef APPLICATION_H
#define APPLICATION_H

// forward declarations
typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct application {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int height;
    int width;
    bool running;
} application_t;

// init_application : initializes the resources for the application
int init_application(application_t *application);

// destroy_application : destroys the allocated resources for the application
int destroy_application(application_t *application);

typedef enum SDL_EventType SDL_EventType;

// handle_events : checks for events and returns them
SDL_EventType handle_events(application_t *application);

#endif