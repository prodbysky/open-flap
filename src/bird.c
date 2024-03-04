#include "bird.h"

bird_t bird_new(int x, int y) {
    bird_t bird;
    bird.rect = textured_square_new(x, y, BIRD_WIDTH, BIRD_HEIGHT, BIRD_TEXTURE_PATH);
    bird.velocity = 0.0;
    bird.offset = 0;
    bird.jumpPower = BIRD_JUMP_POWER;
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
