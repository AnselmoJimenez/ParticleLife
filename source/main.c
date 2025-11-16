#include <stdio.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "styles/style_dark.h"

#include "../include/interface.h"

int main(void) {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Particle Life");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    GuiLoadStyleDark(); // Load Dark Style

    Font font = LoadFont("./assets/fonts/OpenSans.ttf");

    // Main game loop
    while (!WindowShouldClose()) {
        // Draw
        BeginDrawing();
        ClearBackground((Color) {20, 20, 18, 255});

        // GUI Controls
        init_interface(font);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}