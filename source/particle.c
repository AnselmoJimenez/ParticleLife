#include <stdio.h>
#include <stdlib.h>

#include "../include/particle.h"

#define RADIUS 3
#define NUMCLASSIFIERS  6

// new_particle : return a new particle object
particle_t new_particle(Vector2 position, float acceleration, float velocity, Color color) {
    return (particle_t) {
        .position = position,
        .acceleration = acceleration,
        .velocity = velocity,
        .color = color
    };
}

// generate_particles : fills the array of particles
particle_t *generate_particles(int screen_width, int screen_height, unsigned int numtypes) {
    particle_t *particles = (particle_t *) malloc(MAXPARTICLES * sizeof(particle_t));

    // guard clauses
    if (numtypes > NUMCLASSIFIERS) return particles;
    
    // classifiers
    Color classifier[NUMCLASSIFIERS] = { RED, GREEN, BLUE, PINK, YELLOW, PURPLE };
    
    for (int i = 0; i < MAXPARTICLES; i++) {
        particles[i] = new_particle(
            (Vector2) {
                rand() % screen_width - 10,
                rand() % screen_height - 10
            },
            10.0f,
            75.0f,
            classifier[i % numtypes]
        );
    }

    return particles;
}

// destroy_particles : frees particle data
void destroy_particles(particle_t *particles) {
    free(particles);
}

// draw_particle : draws a particle to the screen based on position
void draw_particle(particle_t particle) {
    DrawCircle(particle.position.x, particle.position.y, RADIUS, particle.color);
}