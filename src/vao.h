#ifndef VAO_H
#define VAO_H

#include "../include/GLEW/glew.h"

typedef struct {
    GLuint ID;
} vao_t;

vao_t vao_new();
void vao_bind(vao_t vao);
void vao_unbind();

#endif // VAO_H
