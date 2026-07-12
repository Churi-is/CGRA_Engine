#pragma once
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct {
    unsigned int ID;
} Shader;

Shader shader_create_from_paths(char* vertPath, char* fragPath);
Shader shader_create_from_strings(char* vertString, char* fragString);
void shader_use(Shader s);
void shader_set_bool(Shader s, char* name, char value);
void shader_set_int(Shader s, char* name, int value);
void shader_set_float(Shader s, char* name, float value);