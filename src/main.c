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

typedef struct {
    square_t rect;
    float velocity; // y velocity
    float offset;    // to avoid updating the vertices every frame
    float jumpPower;
} bird_t;
int main(int argc, char *argv[]) {
    window_t window = window_new(WINDOW_WIDTH, WINDOW_HEIGHT, "Open flap");

    if (window.window == NULL) {
        fprintf(stderr, "Failed to create window!\n");
        glfwTerminate();
        return 0;
    }
    window_set_callback(&window);

    textured_square_t square = textured_square_new(350, 350, 100, 100, "../resources/pop-cat.png");

    shader_t defaultShader = shader_new("default.vert.glsl", "default.frag.glsl");
    shader_t textureShader = shader_new("texture.vert.glsl", "texture.frag.glsl");
    mat4 projection;

    glm_ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -10.0f, 10.0f, projection);

    while (!window_should_close(window)) {
        window_clear(0.035f, 0.05f, 0.2f, 1.0f);

        textured_square_draw(square, textureShader, projection);
        if (window_key_down(window, GLFW_KEY_A)) {
            LOG("Key a is pressed!\n");
        }
        window_swap(window);
    }
   
    shader_delete(defaultShader);
    shader_delete(textureShader);
    window_delete(window);

    return 0;
}
