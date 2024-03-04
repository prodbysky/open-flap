#ifndef TEXTURE_H
#define TEXTURE_H

#include "../include/GLEW/glew.h"
#include "../include/stbi_image.h"

#include "log.h"

typedef struct {
    GLuint ID;
} texture_t;

texture_t texture_new(const char* name);
void texture_bind(texture_t texture);
void texture_unbind();

#endif // TEXTURE_H
