#include "square.h"
#include "ebo.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"

square_t square_new(float *size, float *position, vao_t vao) {
    square_t square;
    GLfloat vertices[] = {
        position[0],           position[1] + size[1], 1.0f,
        position[0] + size[0], position[1] + size[1], 1.0f,
        position[0],           position[1],           1.0f,
        position[0] + size[0], position[1],           1.0f,
    };

    GLint indices[] = {
        0, 1, 2,
        2, 3, 1,
    };
    
    square.vbo = vbo_new(vertices, sizeof(vertices), GL_STATIC_DRAW);
    square.ebo = ebo_new(indices, sizeof(indices), GL_STATIC_DRAW);

    vao_bind(vao);
    vbo_bind(square.vbo);
    vao_add_attribute_f(vao, 0, 3, sizeof(float) * 3, 0, square.vbo);
    vao_enable_attribute(0);
    vbo_unbind();
    vao_unbind();

    return square;
}

void square_draw(square_t square, vao_t vao, shader_t shader) {
    shader_use(shader);
    vao_bind(vao);
    vbo_bind(square.vbo);
    ebo_bind(square.ebo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vbo_unbind();
    vao_unbind();
    ebo_unbind();
}
