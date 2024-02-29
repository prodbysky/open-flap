#include "square.h"
#include "ebo.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
square_t square_new(float x, float y, float w, float h) {
    square_t square;

    GLfloat vertices[] = {
         x,   y, 1.0f, // Top left
         x - w, y, 1.0f, // Top right
         x - w, y - h, 1.0f, // Bottom right
         x, y - h, 1.0f, // Bottom left
    };
    GLint indices[] = {
        0, 3, 2,
        0, 1, 2
    };

    glm_mat4_identity(square.model);
    
    square.vao = vao_new();
    vao_bind(square.vao);
    square.vbo = vbo_new(vertices, sizeof(vertices), GL_STATIC_DRAW);
    square.ebo = ebo_new(indices, sizeof(indices), GL_STATIC_DRAW);

    vao_bind(square.vao);
    vbo_bind(square.vbo);
    ebo_bind(square.ebo);
    vao_add_attribute_f(square.vao, 0, 3, sizeof(float) * 3, 0, square.vbo);
    vao_enable_attribute(0);
    vao_unbind();
    vbo_unbind();
    ebo_unbind();

    return square;
}

void square_draw(square_t square, shader_t shader, mat4 proj) {
    shader_use(shader); 

    shader_set_uniform_mat4(shader, proj, "projection");
    shader_set_uniform_mat4(shader, square.model, "model");
    shader_set_uniform_mat4(shader, GLM_MAT4_IDENTITY, "view");

    vao_bind(square.vao);
    vbo_bind(square.vbo);
    ebo_bind(square.ebo);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vbo_unbind();
    vao_unbind();
    ebo_unbind();
}
