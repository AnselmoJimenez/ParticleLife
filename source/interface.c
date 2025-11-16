#include <stdio.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "../include/interface.h"

typedef struct interface {
    unsigned int height;
    unsigned int width;
} interface_t;

void init_interface(void) {
    interface_t interface;
    interface.height = GetScreenHeight();
    interface.width = 265;

    // Draw the interface and menu
    GuiPanel((Rectangle) {0, 0, interface.width, interface.height}, NULL);
    GuiLabel((Rectangle) {15, 10, 168, 25}, "Particle Life Simulation");
    GuiLabel((Rectangle) {15, 20, 168, 25}, "Particles");
}