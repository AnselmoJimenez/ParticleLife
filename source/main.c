#include <stdio.h>

#include "raylib.h"
#include "../include/interface.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Particle Life");
    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) {
        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        // GUI Controls
        init_interface();

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}