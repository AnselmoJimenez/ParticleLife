#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

typedef struct particle {
    Vector2 position;
    float acceleration;
    float velocity;
    Color color;
} particle_t;

#define MAXPARTICLES    1024

// new_particle : return a new particle object
particle_t new_particle(Vector2 position, float acceleration, float velocity, Color color);

// draw_particle : draws a particle to the screen based on position
void draw_particle(particle_t particle);

#endif