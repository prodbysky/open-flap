#include <stdlib.h>
#include <stdio.h>

#include "../include/GLEW/glew.h"
#include "../include/GLFW/glfw3.h"

#define WINDOW_WIDTH 640.0f
#define WINDOW_HEIGHT 640.0f

#include "square.h"
#include "shader.h"
#include "log.h"


GLFWwindow* init_window(int w, int h, char* title);

int main(int argc, char *argv[]) {
    GLFWwindow* window = init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Open flap");

    if (window == NULL) {
        fprintf(stderr, "Failed to create window!\n");
        glfwTerminate();
        return 0;
    }

    square_t square = square_new(350, 350, 100, 100);

    shader_t shader = shader_new("default.vert.glsl", "default.frag.glsl");
    mat4 projection;
    glm_ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -10.0f, 10.0f, projection);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.035f, 0.05f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        square_draw(square, shader, projection);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
   
    shader_delete(shader);
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

    LOG("[LOG]: Successfully created a window and initialized OpenGL functions\n");

    return window;
}
