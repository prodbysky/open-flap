#include <stdlib.h>
#include <stdio.h>

#include "../include/GLEW/glew.h"
#include "../include/GLFW/glfw3.h"


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "log.h"

const static GLfloat vertices[] = {
     -0.1f, -0.1f, 1.0f, // Bottom left
      0.1f, -0.1f, 1.0f, // Bottom right
     -0.1f,  0.1f, 1.0f, // Top left
      0.1f,  0.1f, 1.0f, // Top right
};
const static GLint indices[] = {
    0, 1, 2, // Top triangle
    2, 3, 1,  // Bottom triangle
};

GLFWwindow* init_window(int w, int h, char* title);

int main(int argc, char *argv[]) {
    GLFWwindow* window = init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Open flap");

    if (window == NULL) {
        fprintf(stderr, "Failed to create window!\n");
        glfwTerminate();
        return 0;
    }

    vao_t vao = vao_new();
    vao_bind(vao);

    vbo_t vbo = vbo_new(vertices, sizeof(vertices), GL_STATIC_DRAW);
    vbo_bind(vbo);

    ebo_t ebo = ebo_new(indices, sizeof(indices), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    vbo_unbind();
    vao_unbind();
    ebo_unbind();

    shader_t shader = shader_new("vertex.glsl", "fragment.glsl");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.035f, 0.05f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_use(shader);
        vao_bind(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
