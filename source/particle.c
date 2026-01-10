#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"

#include "../include/particle.h"
#include "../include/application.h"

// color classes classified by class_t
static SDL_Color rgba[NUMCLASSES] = {
    { 255,  59,  48, 255 },
    {   0, 122, 255, 255 }, 
    {  52, 199,  89, 255 },
    { 255, 204,   0, 255 },
    { 175,  82, 222, 255 },
    { 255, 149,   0, 255 },
    { 50,  173, 230, 255 },
    { 255, 127, 255, 255 }
};

// new_particle : creates a new particle
static particle_t new_particle(vector2D_t position, class_t class) {
    return (particle_t) {
        .position = position,
        .acceleration = (vector2D_t) { .x = 0.0f, .y = 0.0f },
        .velocity = (vector2D_t) { .x = 0.0f, .y = 0.0f },
        .class = class
    };
}

// init_particles : creates a pointer to an array of n particles
particle_t *init_particles(application_t *application, unsigned int n) {
    // initialize particles array
    particle_t *particles = (particle_t *) malloc(n * sizeof(particle_t));

    // fill the particles array
    for (unsigned int i = 0; i < n; i++) {
        particles[i] = new_particle(
            (vector2D_t) { 
                SDL_rand(application->width), 
                SDL_rand(application->height) 
            },
            i % NUMCLASSES
        );
    }

    return particles;
}

// destroy_particles : destroys (frees) the particles array
void destroy_particles(particle_t *particles) {
    free(particles);
}

// fill_particle : fills in the particle based on it's bounds
static void fill_particle(application_t *application, int start, int end, int particle_y, int y_offset) {
    for (int i = start; i < end + 1; i++) {
        SDL_RenderPoint(application->renderer, i, particle_y + y_offset);
        SDL_RenderPoint(application->renderer, i, particle_y - y_offset);
    }
}

// draw_particle : draws a particle to the screen
void draw_particle(application_t *application, particle_t particle) {
    // set draw color of the particle
    // R, G, B, A
    SDL_SetRenderDrawColor(application->renderer, rgba[particle.class].r, rgba[particle.class].g, rgba[particle.class].b, rgba[particle.class].a);

    // midpoint algorithm for drawing circles
    fill_particle(application, particle.position.x - RADIUS, particle.position.x + RADIUS, particle.position.y, 0);

    int x = RADIUS;
    int y = 0;
    int p = 1 - RADIUS;
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

        fill_particle(application, particle.position.x - x, particle.position.x + x, particle.position.y, y);
    
        if (x != y)
            fill_particle(application, particle.position.x - y, particle.position.x + y, particle.position.y, x);
    }
}

