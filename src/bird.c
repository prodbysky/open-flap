#include "bird.h"

bird_t bird_new(int x, int y, int w, int h) {
    bird_t bird;
    bird.rect = textured_square_new(x, y, w, h, "bird.png");
    bird.velocity = 0.0;
    bird.offset = 0;
    bird.jumpPower = 10;
    return bird;
}

void bird_update(bird_t* bird, window_t window) {
    if (window_key_down(window, GLFW_KEY_SPACE)) {
        bird->velocity = bird->jumpPower;
    } else {
        bird->velocity += GRAVITY;
    }
    bird->offset += bird->velocity; 
    textured_square_move(&bird->rect, 0, bird->velocity);
}
