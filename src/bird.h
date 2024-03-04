#ifndef BIRD_H
#define BIRD_H

#include "textured_square.h"
#include "window.h"
#include "../include/GLFW/glfw3.h"

#define GRAVITY -0.981f 

typedef struct {
    textured_square_t rect;
    float velocity; // y velocity
    float offset;    // to avoid updating the vertices every frame
    float jumpPower;
} bird_t;

bird_t bird_new(int x, int y, int w, int h);

void bird_update(bird_t* bird, window_t window);

#endif // BIRD_H
