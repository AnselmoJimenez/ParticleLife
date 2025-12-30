#ifndef IMGUI_H
#define IMGUI_H

typedef struct context {
    int hot;
    int active;
    float mouse_x;
    float mouse_y;
    int mouse_press;
} context_t;

#define MENU_DEFAULT_WIDTH  200

#endif