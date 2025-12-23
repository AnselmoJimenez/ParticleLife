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
    { 255,  45,  85, 255 }
};

// new_particle : creates a new particle
particle_t new_particle(vector2D_t position, class_t class) {
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

// draw_particle : draws a particle to the screen
void draw_particle(application_t *application, particle_t particle) {
    // set draw color of the particle
    // R, G, B, A
    SDL_SetRenderDrawColor(application->renderer, rgba[particle.class].r, rgba[particle.class].g, rgba[particle.class].b, rgba[particle.class].a);

    // midpoint algorithm for drawing circles
    for (int x = particle.position.x - RADIUS; x < particle.position.x + RADIUS + 1; x++) {
        SDL_RenderPoint(application->renderer, x, particle.position.y);
        SDL_RenderPoint(application->renderer, x, particle.position.y);
    }

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

        // drawing the generated point and its reflection
        for (int i = particle.position.x - x; i < particle.position.x + x + 1; i++) {
            SDL_RenderPoint(application->renderer, i, particle.position.y + y);
            SDL_RenderPoint(application->renderer, i, particle.position.y - y);
        }
    
        if (x != y) {
            // bottom
            for (int i = particle.position.x - y; i < particle.position.x + y + 1; i++) {
                SDL_RenderPoint(application->renderer, i, particle.position.y + x);
                SDL_RenderPoint(application->renderer, i, particle.position.y + x);
            }
            
            // top
            for (int i = particle.position.x - y; i < particle.position.x + y + 1; i++) {
                SDL_RenderPoint(application->renderer, i, particle.position.y - x);
                SDL_RenderPoint(application->renderer, i, particle.position.y - x);
            }
        }
    }
}

