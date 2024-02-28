#ifndef SQUARE_H
#define SQUARE_H

#include "../include/GLEW/glew.h"
#include "../include/cglm/cglm.h"

#include "shader.h"
#include "ebo.h"
#include "vbo.h"
#include "vao.h"

typedef struct {
    vbo_t vbo; 
    ebo_t ebo;
    vec2 position; 
} square_t;

square_t square_new(float *size, float *position, vao_t vao);
void square_draw(square_t square, vao_t vao, shader_t shader);

#endif // SQUARE_H
