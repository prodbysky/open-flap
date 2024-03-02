#ifndef TEXTURED_SQUARE_H
#define TEXTURED_SQUARE_H

#include "../include/cglm/cglm.h"

#include "shader.h"
#include "texture.h"
#include "vao.h"
#include "ebo.h"

typedef struct {
    texture_t texture;
    vao_t vao;
    vbo_t vbo; 
    ebo_t ebo;
    mat4 model;
} textured_square_t;

textured_square_t textured_square_new(float x, float y, float w, float h, const char* textureName);
void textured_square_draw(textured_square_t square, shader_t shader, mat4 proj);
void textured_square_move(textured_square_t* square, float dx, float dy);

#endif // TEXTURED_SQUARE_H
