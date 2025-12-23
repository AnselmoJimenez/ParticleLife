#ifndef PARTICLE_H
#define PARTICLE_H

#include "SDL_pixels.h"

typedef struct vector2D {
    float x;
    float y;
} vector2D_t;

typedef struct application application_t;

#define NUMCLASSES  8

// index of each color class within color[]
typedef enum classifier {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    PURPLE,
    PINK,
} class_t;

#define RGBA_WHITE  255, 255, 255, 255
#define RGBA_BLACK    0,   0,   0, 255

typedef struct particle {
    vector2D_t position;        // position of the particle (x, y)
    vector2D_t acceleration;    // acceleration of the particle (x, y)
    vector2D_t velocity;        // velocity of the particle (x, y)
    class_t class;              // class (color) of the particle (r, g, b, a)
} particle_t;

#define RADIUS      20
#define DIAMETER    (2 * RADIUS)

// new_particle : creates a new particle
particle_t new_particle(vector2D_t position, class_t class);

// draw_particle : draws a particle to the screen
void draw_particle(application_t *application, particle_t particle);

#endif