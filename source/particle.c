#include <stdio.h>

#include "../include/particle.h"

#define RADIUS 3

// new_particle : return a new particle object
particle_t new_particle(Vector2 position, float acceleration, float velocity, Color color) {
    return (particle_t) {
        .position = position,
        .acceleration = acceleration,
        .velocity = velocity,
        .color = color
    };
}

// draw_particle : draws a particle to the screen based on position
void draw_particle(particle_t particle) {
    DrawCircle(particle.position.x, particle.position.y, RADIUS, particle.color);
}