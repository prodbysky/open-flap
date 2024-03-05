#ifndef BIRD_H
#define BIRD_H

#include "textured_square.h"
#include "window.h"
#include "../include/GLFW/glfw3.h"


// Bird configuration
#define GRAVITY -0.61f 
#define BIRD_TEXTURE_PATH "bird.png"
#define BIRD_JUMP_POWER 10
#define BIRD_HEIGHT 64
#define BIRD_WIDTH BIRD_HEIGHT

typedef struct {
    textured_square_t rect;
    float velocity; // y velocity
    float offset;    // to avoid updating the vertices every frame
    float jumpPower;
} bird_t;

bird_t bird_new(int x, int y);
void bird_update(bird_t* bird, window_t window);

#endif // BIRD_H
