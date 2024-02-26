#include <stdlib.h>
#include <stdio.h>

#include "../include/GLEW/glew.h"
#include "../include/GLFW/glfw3.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#define LOGGING
#ifdef LOGGING
#define LOG(...) fprintf(stderr, __VA_ARGS__);
#else
#define LOG(...) 
#endif

static GLfloat vertices[] = {
     0,            WINDOW_HEIGHT, 1.0f, // Bottom left
     WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, // Bottom right
     0,            0,             1.0f, // Top left
     WINDOW_WIDTH, 0,             1.0f, // Top right
};
static GLint indices[] = {
    0, 1, 2, // Top triangle
    2, 3, 1,  // Bottom triangle
};

GLFWwindow* init_window(int w, int h, char* title);
char* read_file(char* name);

int main(int argc, char *argv[]) {
    GLFWwindow* window = init_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Open flap");

    if (window == NULL) {
        fprintf(stderr, "Failed to create window!\n");
        glfwTerminate();
        return 0;
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = read_file("vertex.glsl");
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = read_file("fragment.glsl");
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    GLuint shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);

    glLinkProgram(shader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.035f, 0.05f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
   
    glDeleteProgram(shader);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

GLFWwindow* init_window(int w, int h, char* title) {
    glfwInit();

    // Tell OpenGL to use OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(w, h, title, NULL, NULL);

    if (window == NULL) {
        LOG("[ERROR]: Failed to create GLFW window\n");
        return NULL;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        LOG("[ERROR]: Failed to initialize GLEW\n");
        return NULL;
    }

    glViewport(0, 0, w, h);

    LOG("[LOG]: Successfully created a window and initialized OpenGL functions\n");

    return window;
}

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
