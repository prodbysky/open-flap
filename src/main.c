#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "square.h"
#include "window.h"
#include "textured_square.h"
#include "shader.h"
#include "log.h"
#include "bird.h"

int main(int argc, char *argv[]) {
    window_t window = window_new(WINDOW_WIDTH, WINDOW_HEIGHT, "Open flap");

    if (window.window == NULL) {
        fprintf(stderr, "Failed to create window!\n");
        glfwTerminate();
        return 0;
    }
    window_set_callback(&window);

    shader_t defaultShader = shader_new("default.vert.glsl", "default.frag.glsl");
    shader_t textureShader = shader_new("texture.vert.glsl", "texture.frag.glsl");
    mat4 projection;
    // glm_ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -10.0f, 10.0f, projection);
    glm_ortho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -10.0f, 10.0f, projection);

    bird_t bird = bird_new(128, 256);

    double previousTime, currentTime, elapsedTime;
    currentTime = glfwGetTime();
    previousTime = currentTime;

    while (!window_should_close(window)) {
        currentTime = glfwGetTime();
        elapsedTime = currentTime - previousTime;

        if (elapsedTime >= TICK_DURATION) {
            bird_update(&bird, window);
            previousTime = currentTime;
        }

        window_clear(0.035f, 0.05f, 0.2f, 1.0f);

        textured_square_draw(bird.rect, textureShader, projection);
        window_swap(window);
    }
   
    shader_delete(defaultShader);
    shader_delete(textureShader);
    window_delete(window);

    return 0;
}
