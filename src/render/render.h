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

Mesh render_create_mesh(float vertices[], unsigned int indices[]);
Material render_create_material(char** vertSource, char** fragSource);

Object render_initialise();

void render_frame(Object* s);