#include "window.h"
#include <string.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    window_t* my_window = glfwGetWindowUserPointer(window);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    my_window->keys[key] = action;
}

window_t window_new(float w, float h, const char *title) {
    glfwInit();

    // Tell OpenGL to use OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_t window;
    memset(window.keys, 0, sizeof(window.keys));
    window.window = glfwCreateWindow(w, h, title,  NULL, NULL);

    if (window.window == NULL) {
        LOG("[ERROR]: Failed to create GLFW window\n");
        return window;
    }

    glfwMakeContextCurrent(window.window);

    // Load OpenGL functions
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        LOG("[ERROR]: Failed to initialize GLEW\n");
        window.window = NULL;
        return window;
    }

    glViewport(0, 0, w, h);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    LOG("[LOG]: Successfully created a window and initialized OpenGL functions\n");

    return window;
}

void window_swap(window_t window) {
    glfwSwapBuffers(window.window);
    glfwPollEvents();
}

void window_clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool window_should_close(window_t window) {
    return glfwWindowShouldClose(window.window);
}

void window_delete(window_t window) {
    glfwDestroyWindow(window.window);
    glfwTerminate();
}

bool window_key_down(window_t window, GLenum key) {
    return window.keys[key];
}

void window_set_callback(window_t* window) {
    glfwSetWindowUserPointer(window->window, window);
    glfwSetKeyCallback(window->window, key_callback);
}
