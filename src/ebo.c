#include "ebo.h"

ebo_t ebo_new(const void *data, size_t size, GLenum usage) {
    ebo_t ebo;
    glGenBuffers(1, &ebo.ID);

    ebo_bind(ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
    ebo_unbind();

    return ebo;
}

void ebo_bind(ebo_t ebo) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.ID);
}

void ebo_unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
