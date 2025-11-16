#include <stdio.h>

#include "raylib.h"
#include "raygui.h"

#include "../include/interface.h"

typedef struct interface {
    unsigned int height;
    unsigned int width;
    unsigned int xoffset;
    unsigned int yoffset;
} interface_t;
interface_t interface;

#define MAX_PARTICLES   1024

void draw_particles_header(Font font) {
    int placeholder = 0;

    // Set text color to white
    GuiSetStyle(VALUEBOX, TEXT_COLOR_NORMAL, ColorToInt(WHITE));

    DrawTextEx(font, "Particles", (Vector2) {interface.xoffset, interface.yoffset}, 22, 2, WHITE);
    interface.yoffset += 30;
    GuiValueBox((Rectangle) {
        .x = interface.width / 2,
        .y = interface.yoffset,
        .width = interface.width / 2 - interface.xoffset,
        .height = 18
    }, "Particle Count ", &placeholder, 0, MAX_PARTICLES, true);
    interface.yoffset += 25;
    GuiSpinner((Rectangle) {
        .x = interface.width / 2,
        .y = interface.yoffset,
        .width = interface.width / 2 - interface.xoffset,
        .height = 18
    }, "Particle Types ", &placeholder, 0, 6, true);
    interface.yoffset += 20;
    GuiLine((Rectangle) {
        .x = interface.xoffset,
        .y = interface.yoffset,
        .width = interface.width - 2 * interface.xoffset,
        .height = 12
    }, NULL);
}

void init_interface(Font font) {
    interface.height = GetScreenHeight();
    interface.width = 256;
    interface.xoffset = 15;
    interface.yoffset = 10;

    // Draw the interface and menu
    GuiPanel((Rectangle) {0, 0, interface.width, interface.height}, NULL);
    DrawTextEx(font, "Particle Life", (Vector2) {interface.xoffset, interface.yoffset}, 32, 2, WHITE);
    interface.yoffset += 25;
    GuiLine((Rectangle) {
        .x = interface.xoffset,
        .y = interface.yoffset,
        .width = interface.width - 2 * interface.xoffset,
        .height = 12
    }, NULL);
    interface.yoffset += 15;
    
    draw_particles_header(font);
}