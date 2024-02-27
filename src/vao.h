#ifndef VAO_H
#define VAO_H

#include "../include/GLEW/glew.h"

#include "vbo.h"

typedef struct {
    GLuint ID;
} vao_t;

vao_t vao_new();
void vao_bind(vao_t vao);
void vao_unbind();
void vao_add_attribute_f(vao_t vao, int index, int count, size_t stride, size_t offset, vbo_t vbo);
void vao_enable_attribute(int index);

#endif // VAO_H
