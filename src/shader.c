#include "shader.h"

char* read_file(char* name) {
    FILE* file = fopen(name, "r"); 
    if (file == NULL) {
        LOG("[ERROR]: Failed open file: %s\n", name);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* string = malloc(sizeof(char) * (fileSize + 1));
    fread(string, sizeof(char), fileSize, file);
    string[fileSize + 1] = 0;

    fclose(file);
    LOG("[LOG]: Successfully read file: %s\n", name);

    return string;
}

shader_t shader_new(char *vertexShaderName, char *fragmentShaderName) {
    shader_t shader;
    
    int success;
    char log[512];

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = read_file(vertexShaderName);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, log);
        LOG("[ERROR]: Failed to compile vertex shader: %s", log);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = read_file("fragment.glsl");
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
        LOG("[ERROR]: Failed to compile fragment shader: %s", log);
    }

    shader.ID = glCreateProgram();
    glAttachShader(shader.ID, vertexShader);
    glAttachShader(shader.ID, fragmentShader);

    glLinkProgram(shader.ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

void shader_use(shader_t shader) {
    glUseProgram(shader.ID);
}

void shader_delete(shader_t shader) {
    glDeleteProgram(shader.ID);
}
