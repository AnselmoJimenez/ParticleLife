#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct particle particle_t;

// gameloop : the main game loop
int gameloop(particle_t *particles, int *screen_width, int *screen_height);

#endif