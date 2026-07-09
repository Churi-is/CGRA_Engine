#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource ="#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

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

void render_initialise(){
    #ifndef NDEBUG
    printf("Initalising OpenGL Buffers.\n");
    #endif
    float vertices[] = {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int vertexShader = 
        render_create_shader(&vertexShaderSource, GL_VERTEX_SHADER);

    unsigned int fragmentShader = 
        render_create_shader( &fragmentShaderSource, GL_FRAGMENT_SHADER);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 0. copy our vertices array in a buffer for OpenGL to use
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    // 2. use our shader program when we want to render an object
    glUseProgram(shaderProgram);

    // 3. now draw the object?
}

void render_frame() {
    glClearColor(0.5f, 0.5, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}