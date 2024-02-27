#ifndef SHADER_H
#define SHADER_H

#include <stdlib.h>
#include <stdio.h>
#include "../include/GLEW/glew.h"
#include "log.h"

typedef struct {
    GLuint ID; 
} shader_t;

// TODO: Set uniforms functions
shader_t shader_new(char* vertexShaderName, char* fragmentShaderName);
void shader_use(shader_t shader);
void shader_delete(shader_t shader);

#endif // SHADER_H
