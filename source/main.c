#include <stdio.h>

#include "../include/particle.h"

#include "raylib.h"

int main(void) {
    const int screen_width = 1280;
    const int screen_height = 720;

    InitWindow(screen_width, screen_height, "Particle Life");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) {
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw Particles
        draw_particle(new_particle((Vector2) {screen_width / 2, screen_height / 2}, 0.0f, 0.0f, BLUE));

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}