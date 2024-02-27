#include "vao.h"
#include "vbo.h"

vao_t vao_new() {
    vao_t vao;
    glGenVertexArrays(1, &vao.ID);
    return vao;
}

void vao_bind(vao_t vao) {
    glBindVertexArray(vao.ID);
}

void vao_unbind() {
    glBindVertexArray(0);
}
void vao_add_attribute_f(vao_t vao, int index, int count, size_t stride, size_t offset, vbo_t vbo) {
    vbo_bind(vbo);
    glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride, (void*)offset);
    vbo_unbind();
}

void vao_enable_attribute(int index) {
    glEnableVertexAttribArray(index);
}
