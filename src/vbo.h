#ifndef VBO_H
#define VBO_H

#include "../include/GLEW/glew.h"

typedef struct {
    GLuint ID; 
} vbo_t;

vbo_t vbo_new(const void *data, size_t size, GLenum usage);
void vbo_bind(vbo_t vbo);
void vbo_unbind();

#endif // VBO_H
