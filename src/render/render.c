#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "render.h"
#include "shader.h"

int render_check_shader(unsigned int shaderID) {
    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
        return 0;
    }
    return 1;
}

unsigned int render_create_shader(char** shaderSource, int shaderType) {
    unsigned int shaderID;
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, shaderSource, NULL);
    glCompileShader(shaderID);
    render_check_shader(shaderID);
    return shaderID;
}

Object render_initialise(){
    #ifndef NDEBUG
    printf("Initalising OpenGL Buffers.\n");
    #endif
    // Triangle verts and indices
    float vertices[] = {
    // positions        // colors
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2
    };

    Mesh mesh = render_create_mesh(vertices, sizeof(vertices), indices, sizeof(indices));
    
    Shader s = shader_create_from_paths("./src/render/shaders/vert.glsl", "./src/render/shaders/frag.glsl");

    Object o = {.mesh=mesh, .s=s};
    return o;
}

// NOTE: could have a output pointer as parameter, save the copying for larger meshes.
Mesh render_create_mesh(const float *vertices, size_t vertex_bytes,
                        const unsigned int *indices, size_t index_bytes) {
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_bytes, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_bytes, indices, GL_STATIC_DRAW);
        
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    Mesh m = {.VAO=VAO, .EBO=EBO, .VBO=VBO};
    return m;
}

void render_frame(Object* o) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int sp = o->s.ID;
    glUseProgram(sp);

    float timeValue = (float)glfwGetTime();
    float greenValue = (float)(sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(sp, "ourColor");
    glUseProgram(sp);
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glBindVertexArray(o->mesh.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}