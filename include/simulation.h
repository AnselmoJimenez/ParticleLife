#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct particle particle_t;

// gameloop : the main game loop
// Input:
//      particle_t *particles
//      int *screen_width
//      int *screen_height
// Output:
//      0 on successful exit
int gameloop(particle_t *, int *, int *);

#endif