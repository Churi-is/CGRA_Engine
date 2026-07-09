#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "render.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

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
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    Mesh mesh = render_create_mesh(vertices, sizeof(vertices), indices, sizeof(indices));
    Material mat = render_create_material(&vertexShaderSource, &fragmentShaderSource);

    Object o = {.mesh=mesh, .mat=mat};
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
        
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    Mesh m = {.VAO=VAO, .EBO=EBO, .VBO=VBO};
    return m;
}

// NOTE: Replace or make another that uses file input instead. also could take in a output pointer if i want to make it a pattern.
Material render_create_material(char** vertSource, char** fragSource) {
    unsigned int vertexShader = 
        render_create_shader(vertSource, GL_VERTEX_SHADER);

    unsigned int fragmentShader = 
        render_create_shader(fragSource, GL_FRAGMENT_SHADER);

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

    Material m = {.shaderProgram=shaderProgram};
    return m;
}

void render_frame(Object* o) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(o->mat.shaderProgram);
    glBindVertexArray(o->mesh.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}