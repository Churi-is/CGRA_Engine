#pragma once

unsigned int render_create_shader(char* shaderSource, int shaderType);
int render_check_shader(unsigned int shaderID);
void render_initialise();
void render_frame();