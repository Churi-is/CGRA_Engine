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

Mesh render_create_mesh(const float *vertices, size_t vertex_bytes,
                        const unsigned int *indices, size_t index_bytes);

Object render_initialise();

void render_frame(Object* s);