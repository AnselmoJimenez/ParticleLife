#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

typedef struct particle {
    Vector2 position;
    float acceleration;
    float velocity;
    Color color;
} particle_t;

#define MAXPARTICLES    1

// new_particle : return a new particle object
// input:
//      Vector2 position
//      float accleration
//      float velocity
//      Color color
// output:
//      particle_t
particle_t new_particle(Vector2 position, float acceleration, float velocity, Color color);

// generate_particles : generate the array of particles
// inputs:
//      int screen_width
//      int screen_height
//      unsigned int numtypes
particle_t *generate_particles(int screen_width, int screen_height, unsigned int numtypes);

// destroy_particles : frees particle data
// inputs:
//      particle_t *particles
void destroy_particles(particle_t *particles);

// draw_particle : draws a particle to the screen based on position
// inputs:
//      particle_t particle
void draw_particle(particle_t particle);

#endif