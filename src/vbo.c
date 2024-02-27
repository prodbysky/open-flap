#include "vbo.h"

vbo_t vbo_new(const void *data, size_t size, GLenum usage) {
    vbo_t vbo;
    glGenBuffers(1, &vbo.ID);
    vbo_bind(vbo);
    
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    vbo_unbind();

    return vbo;
}

void vbo_bind(vbo_t vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
}

void vbo_unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
