#include <stdlib.h>
#include <stdio.h>

#include "../include/GLEW/glew.h"
#include "../include/GLFW/glfw3.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main(int argc, char *argv[]) {
    glfwInit();

    // Tell OpenGL to use OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGl Application", NULL, NULL);

    if (window == NULL) {
        fprintf(stderr, "Failed to create window\n");
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "[ERROR]: %s\n", glewGetErrorString(err));
        return 0;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.035f, 0.05f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
   
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
