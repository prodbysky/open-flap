#include "textured_square.h"
#include "texture.h"

textured_square_t textured_square_new(float x, float y, float w, float h, const char* textureName) {
    textured_square_t square;

    GLfloat vertices[] = {
         x,     y,     1.0f, 1.0f, 1.0f, // Top left
         x - w, y,     1.0f, 0.0f, 1.0f, // Top right
         x - w, y - h, 1.0f, 0.0f, 0.0f, // Bottom right
         x,     y - h, 1.0f, 1.0f, 0.0f, // Bottom left
    };

    GLint indices[] = {
        0, 3, 2,
        0, 1, 2
    };

    square.texture = texture_new(textureName);

    glm_mat4_identity(square.model);
    
    square.vao = vao_new();
    vao_bind(square.vao);
    square.vbo = vbo_new(vertices, sizeof(vertices), GL_STATIC_DRAW);
    square.ebo = ebo_new(indices, sizeof(indices), GL_STATIC_DRAW);

    vao_bind(square.vao);
    vao_add_attribute_f(square.vao, 0, 3, sizeof(float) * 5, 0, square.vbo);
    vao_add_attribute_f(square.vao, 1, 2, sizeof(float) * 5, sizeof(float) * 3, square.vbo);
    vao_enable_attribute(0);
    vao_enable_attribute(1);
    vao_unbind();

    return square;
}

void textured_square_draw(textured_square_t square, shader_t shader, mat4 proj) {
    shader_use(shader); 

    shader_set_uniform_mat4(shader, proj, "projection");
    shader_set_uniform_mat4(shader, square.model, "model");
    shader_set_uniform_mat4(shader, GLM_MAT4_IDENTITY, "view");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, square.texture.ID);
    glUniform1i(glGetUniformLocation(shader.ID, "utexture"), 0);

    vao_bind(square.vao);
    vbo_bind(square.vbo);
    ebo_bind(square.ebo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vbo_unbind();
    vao_unbind();
    ebo_unbind();
}

void textured_square_move(textured_square_t* square, float dx, float dy) {
    glm_translate(square->model, (vec3){dx, dy, 0});
}
