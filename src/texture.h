#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION

#include "../include/GLEW/glew.h"
#include "../include/stbi_image.h"

#include "log.h"

typedef struct {
    GLuint ID;
} texture_t;

texture_t texture_new(const char* name);

#endif // TEXTURE_H
