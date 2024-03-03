#include <stdlib.h>
#include <stdio.h>

#include "../include/GLEW/glew.h"
#include "../include/GLFW/glfw3.h"


#include "textured_square.h"
#include "shader.h"
#include "log.h"

#define WINDOW_HEIGHT 640.0f
#define WINDOW_WIDTH 640.0f

GLFWwindow* init_window(int w, int h, char* title);

int main(int argc, char *argv[]) {
    GLFWwindow* window = init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Open flap");

    if (window == NULL) {
        fprintf(stderr, "Failed to create window!\n");
        glfwTerminate();
        return 0;
    }


    textured_square_t square = textured_square_new(350, 350, 100, 100, "../resources/pop-cat.png");

    shader_t defaultShader = shader_new("default.vert.glsl", "default.frag.glsl");
    shader_t textureShader = shader_new("texture.vert.glsl", "texture.frag.glsl");
    mat4 projection;
    glm_ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -10.0f, 10.0f, projection);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.035f, 0.05f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        textured_square_draw(square, textureShader, projection);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
   
    shader_delete(defaultShader);
    shader_delete(textureShader);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

GLFWwindow* init_window(int w, int h, char* title) {
    glfwInit();

    // Tell OpenGL to use OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(w, h, title, NULL, NULL);

    if (window == NULL) {
        LOG("[ERROR]: Failed to create GLFW window\n");
        return NULL;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        LOG("[ERROR]: Failed to initialize GLEW\n");
        return NULL;
    }

    glViewport(0, 0, w, h);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    LOG("[LOG]: Successfully created a window and initialized OpenGL functions\n");

    return window;
}
