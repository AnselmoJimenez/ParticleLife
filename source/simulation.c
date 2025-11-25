#include <stdio.h>

#include "raylib.h"

#include "../include/simulation.h"
#include "../include/particle.h"

// gameloop : the main game loop
int gameloop(particle_t *particles, int *screen_width, int *screen_height) {
    // Main game loop
    while (!WindowShouldClose()) {
        // Get delta time - time since last frame in seconds
        float dt = GetFrameTime();

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < MAXPARTICLES; i++)
            draw_particle(particles[i]);

        // update particles
        for (int i = 0; i < MAXPARTICLES; i++) {
            particles[i].position.x += particles[i].velocity * dt;
            particles[i].position.y += particles[i].velocity * dt;
            printf("particle[0].position=(.x = %f, .y = %f)\n", particles[i].position.x, particles[i].position.y);

            // if particle is approaching the edge of the screen wrap it around
            if (particles[i].position.x > (float) (*screen_width - 20)) {
                particle_t temp = new_particle(
                    (Vector2) {
                        .x = particles[i].position.x - *screen_width,
                        .y = particles[i].position.y
                    },
                    particles[i].acceleration, 
                    particles[i].velocity, 
                    particles[i].color
                );
                draw_particle(temp);

                if (particles[i].position.x > *screen_width) 
                    particles[i].position.x = temp.position.x;
            }
            else if (particles[i].position.y > (float) (*screen_height - 20)) {
                particle_t temp = new_particle(
                    (Vector2) {
                        .x = particles[i].position.x,
                        .y = particles[i].position.y - *screen_height
                    },
                    particles[i].acceleration,
                    particles[i].velocity,
                    particles[i].color
                );
                draw_particle(temp);

                if (particles[i].position.y > *screen_height) 
                    particles[i].position.y = temp.position.y;
            }
        }

        EndDrawing();
    }

    return 0;
}