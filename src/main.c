#include <stdlib.h>
#include <stdio.h>

#include "../include/GLEW/glew.h"
#include "../include/GLFW/glfw3.h"

#include "window.h"
#include "textured_square.h"
#include "square.h"
#include "shader.h"
#include "log.h"

#define WINDOW_HEIGHT 640.0f
#define WINDOW_WIDTH 640.0f

#define GRAVITY -0.981f 

typedef struct {
    textured_square_t rect;
    float velocity; // y velocity
    float offset;    // to avoid updating the vertices every frame
    float jumpPower;
} bird_t;

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

int main(int argc, char *argv[]) {
    window_t window = window_new(WINDOW_WIDTH, WINDOW_HEIGHT, "Open flap");

    if (window.window == NULL) {
        fprintf(stderr, "Failed to create window!\n");
        glfwTerminate();
        return 0;
    }
    window_set_callback(&window);

    bird_t bird = bird_new(128, 256, 64, 64);

    shader_t defaultShader = shader_new("default.vert.glsl", "default.frag.glsl");
    shader_t textureShader = shader_new("texture.vert.glsl", "texture.frag.glsl");
    mat4 projection;

    glm_ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -10.0f, 10.0f, projection);

    while (!window_should_close(window)) {
        bird_update(&bird, window);
        window_clear(0.035f, 0.05f, 0.2f, 1.0f);

        textured_square_draw(bird.rect, textureShader, projection);
        window_swap(window);
    }
   
    shader_delete(defaultShader);
    shader_delete(textureShader);
    window_delete(window);

    return 0;
}
