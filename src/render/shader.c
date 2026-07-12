#pragma once
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <stdlib.h>

void read_file(const char* path, char** out) {
    long length;
    FILE* fp = fopen(path, "rb");
    if (fp == NULL) {
        #ifndef NDEBUG
        printf("Cant open %s\n", path);
        #endif
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = malloc((size_t)length + 1);
    if (!buffer) {
        #ifndef NDEBUG
        printf("Could not assign memory to load shader files. %s\n", path);
        #endif
        fclose(fp);
        exit(1);
    }

    fread(buffer, 1, (size_t)length, fp);
    buffer[length] = '\0';
    fclose(fp);

    *out = buffer;
}

unsigned int shader_register_shader(char** shaderSource, int shaderType) {
    unsigned int shaderID;
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, shaderSource, NULL);
    glCompileShader(shaderID);
    render_check_shader(shaderID);
    return shaderID;
}

Shader shader_create_from_paths(char* vertPath, char* fragPath) {
    char* vertShaderString = NULL;
    char* fragShaderString = NULL;

    read_file(vertPath, &vertShaderString);
    read_file(fragPath, &fragShaderString);

    unsigned int vertexShader = 
        render_create_shader(vertShaderString, GL_VERTEX_SHADER);

    unsigned int fragmentShader = 
        render_create_shader(fragShaderString, GL_FRAGMENT_SHADER);

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    Shader s = {shaderProgram};

    return s;
}

Shader shader_create_from_strings(char* vertString, char* fragString) {

}
void shader_use(Shader s) {
    
}
void shader_set_bool(Shader s, char* name, char value) {
    
}
void shader_set_int(Shader s, char* name, int value) {
    
}
void shader_set_float(Shader s, char* name, float value) {
    
}