#include <stdlib.h>
#include <stdio.h>

#include "../include/GLEW/glew.h"
#include "../include/GLFW/glfw3.h"

int main(int argc, char *argv[]) {
    glfwInit();


    // Tell OpenGL to use OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGl Application", NULL, NULL);

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

    // Area where OpenGL will render to
    glViewport(0, 0, 800, 800);

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
