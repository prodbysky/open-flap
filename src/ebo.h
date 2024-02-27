#ifndef EBO_H
#define EBO_H

#include "../include/GLEW/glew.h"

typedef struct {
    GLuint ID;
} ebo_t;

ebo_t ebo_new(const void *data, size_t size, GLenum usage);
void ebo_bind(ebo_t ebo);
void ebo_unbind();

#endif // EBO_H
