#include <stdio.h>

#include "SDL.h"

#include "../include/application.h"
#include "../include/imgui.h"

// init_gui : initializes the gui context
void init_gui(application_t *application, context_t *context) {
    context->container.height = application->height;
    context->container.width = DEFAULT_GUI_WIDTH;
    context->container.padding = CONTAINER_PADDING;
    context->container.x = context->container.padding;
    context->container.y = context->container.padding;
    
    context->active = -1;
    context->hot = -1;

    context->mouse.x = 0.0f;
    context->mouse.y = 0.0f;
    context->mouse.click = 0;
}

#define MENU_GRAY    50,  50,  50, 255

// draw_container : draws the container of the gui
static void draw_container(application_t application, container_t container) {
    SDL_SetRenderDrawColor(application.renderer, MENU_GRAY);

    int rounded_radius = 50;
    
    // draw the rectangular portions
    for (int y = 0; y < container.height; y++) {
        if (y < rounded_radius || y > container.height - rounded_radius) {
            for (int x = 0; x < container.width - rounded_radius; x++)
                SDL_RenderPoint(application.renderer, x, y);
        }
        else {
            for (int x = 0; x < container.width; x++)
                SDL_RenderPoint(application.renderer, x, y);
        }
    }

    // draw curved portions
    int x = rounded_radius;
    int y = 0;
    int p = 1 - rounded_radius;
    while (x > y) {
        y++;

        // Midpoint is inside or on the perimeter
        if (p <= 0) p = p + 2*y + 1;
        else {  // midpoint is outside the perimeter
            x--;
            p = p + 2*y - 2*x + 1;
        }

        // all points found 
        if (x < y) break;

        for (int i = container.width - rounded_radius; i < container.width - rounded_radius + x; i++) {
            SDL_RenderPoint(application.renderer, i, rounded_radius - y);
            SDL_RenderPoint(application.renderer, i, (container.height - rounded_radius) + y);
        }

        if (x != y) {
            for (int i = container.width - rounded_radius; i < container.width - rounded_radius + y; i++) {
                SDL_RenderPoint(application.renderer, i, rounded_radius - x);
                SDL_RenderPoint(application.renderer, i, (container.height - rounded_radius) + x);
            }
        }
    }
}

// draw_gui : draws the context of the gui
void draw_gui(application_t application, context_t context) {
    draw_container(application, context.container);
}
