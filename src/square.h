#ifndef SQUARE_H
#define SQUARE_H

#include "../include/GLEW/glew.h"
#include "../include/cglm/cglm.h"

#include "ebo.h"
#include "vbo.h"

typedef struct {
    vbo_t vbo; 
    ebo_t ebo;
    vec2 position; 
} square_t;

square_t square_new(vec2 size, vec2 position);

#endif // SQUARE_H
