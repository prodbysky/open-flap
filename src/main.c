#include <stdlib.h>
#include <stdio.h>

#include "square.h"
#include "window.h"
#include "textured_square.h"
#include "shader.h"
#include "log.h"
#include "bird.h"
#include "bar.h"

#define WINDOW_HEIGHT 640.0f
#define WINDOW_WIDTH 640.0f

int main(int argc, char *argv[]) {
    window_t window = window_new(WINDOW_WIDTH, WINDOW_HEIGHT, "Open flap");

    if (window.window == NULL) {
        fprintf(stderr, "Failed to create window!\n");
        glfwTerminate();
        return 0;
    }
    window_set_callback(&window);

    bird_t bird = bird_new(128, 256, 64, 64);
    bar_t bar = bar_new(128, 256, 64, 256, 5);

    shader_t defaultShader = shader_new("default.vert.glsl", "default.frag.glsl");
    shader_t textureShader = shader_new("texture.vert.glsl", "texture.frag.glsl");
    mat4 projection;

    glm_ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -10.0f, 10.0f, projection);

    while (!window_should_close(window)) {
        bar_update(&bar, window);
        bird_update(&bird, window);
        window_clear(0.035f, 0.05f, 0.2f, 1.0f);

        textured_square_draw(bird.rect, textureShader, projection);
        square_draw(bar.rect, defaultShader, projection);
        window_swap(window);
    }
   
    shader_delete(defaultShader);
    shader_delete(textureShader);
    window_delete(window);

    return 0;
}
