#pragma once

typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
} Mesh;

typedef struct {
    unsigned int shaderProgram;
} Material;

typedef struct {
    Mesh mesh;
    Material mat;
} Object;

// so a mesh is a VAO + VBO + EBO
// each shaderProgram is a Material type

int render_check_shader(unsigned int shaderID);

unsigned int render_create_shader(char** shaderSource, int shaderType);

Mesh render_create_mesh(const float *vertices, size_t vertex_bytes,
                        const unsigned int *indices, size_t index_bytes);
Material render_create_material(char** vertSource, char** fragSource);

Object render_initialise();

void render_frame(Object* s);