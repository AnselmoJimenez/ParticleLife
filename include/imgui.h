#ifndef IMGUI_H
#define IMGUI_H

typedef struct application application_t;

// mouse struct to track mouse position
typedef struct mouse {
    float x;
    float y;
    int click;
} mouse_t;

// container struct to track GUI panel information
typedef struct container {
    int height;     // height of container
    int width;      // width of container
    int padding;    // padding of the container
    int x;          // next available x for widgets
    int y;          // next available y for widgets
} container_t;

// context struct to keep track of the GUI context's information
typedef struct context {
    container_t container;
    int hot;
    int active;
    mouse_t mouse;
} context_t;

extern context_t context;

#define DEFAULT_GUI_WIDTH   256
#define CONTAINER_PADDING   8

// init_gui : initializes the gui context
void init_gui(application_t *application, context_t *context);

// draw_gui : draws the context of the gui
void draw_gui(application_t application, context_t context);

#endif