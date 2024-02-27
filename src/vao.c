#include "vao.h"

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
