#include <stdio.h>
#include <stdlib.h>

#include "../include/particle.h"
#include "../include/simulation.h"

#include "raylib.h"

#define NUMCLASSIFIERS  6
Color classifier[NUMCLASSIFIERS] = { RED, GREEN, BLUE, PINK, YELLOW, PURPLE };

int main(void) {
    int screen_width = 1280;
    int screen_height = 720;

    InitWindow(screen_width, screen_height, "Particle Life");

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);   // Set game to run at 60 frames-per-second

    particle_t *particles = generate_particles(screen_width, screen_height, 3);

    if (gameloop(particles, &screen_width, &screen_height) != 0) {
        destroy_particles(particles);
        CloseWindow();
        return 1;
    }

    destroy_particles(particles);

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}