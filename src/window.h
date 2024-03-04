#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#include "../include/GLEW/glew.h"
#include "../include/GLFW/glfw3.h"
#include "../include/cglm/cglm.h"

#include "log.h"

typedef struct {
    GLFWwindow* window;
    bool keys[348];
} window_t;

window_t window_new(float w, float h, const char *title);
void window_set_callback(window_t* window);
void window_clear(float r, float g, float b, float a);
void window_swap(window_t window);
void window_delete(window_t window);
bool window_should_close(window_t window);
bool window_key_down(window_t window, GLenum key);

#endif
