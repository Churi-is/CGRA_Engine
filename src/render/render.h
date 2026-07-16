#pragma once
#include "shader.h"

typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
} Mesh;

typedef struct {
    Mesh mesh;
    Shader s;
    int texture1ID;
    int texture2ID;
} Object;

Mesh render_create_mesh();

Object render_initialise();

void render_frame(Object* s);