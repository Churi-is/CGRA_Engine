#pragma once

typedef struct {
    unsigned int VAO;
    unsigned int shaderProgram;
} RenderState;

int render_check_shader(unsigned int shaderID);

unsigned int render_create_shader(char** shaderSource, int shaderType);

RenderState render_initialise();

void render_frame(RenderState* s);