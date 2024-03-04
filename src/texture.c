#include "texture.h"

texture_t texture_new(const char *name) {
    texture_t tex;
    glGenTextures(1, &tex.ID);
    texture_bind(tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(name, &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        LOG("[LOG]: Loaded image: %s\n", name);
    } else {
        LOG("[ERROR]: Failed to load image: %s\n", name);
        return (texture_t){0};
    }

    stbi_image_free(data);
    return tex;
}

void texture_bind(texture_t texture) {
    glBindTexture(GL_TEXTURE_2D, texture.ID);
}

void texture_unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
