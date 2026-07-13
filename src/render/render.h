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
} Object;

// so a mesh is a VAO + VBO + EBO
// each shaderProgram is a Material type

Mesh render_create_mesh(const float *vertices, size_t vertex_bytes,
                        const unsigned int *indices, size_t index_bytes);

Object render_initialise();

void render_frame(Object* s);