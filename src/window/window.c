#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

void window_destroy() {
    glfwTerminate();
}

GLFWwindow* window_init() {
    #ifndef NDEBUG
    printf("Initalising GLFW.\n");
    #endif
    glfwInit();
    // glfwWindowHint configures window options. Prams are (Option Enum, Value), Eg here sets the verison to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create the window
    GLFWwindow* window = glfwCreateWindow(800, 600, "CGRA Engine", NULL, NULL);
    if (window == NULL)
    {
        #ifndef NDEBUG
        printf("Failed to create GLFW window\n");
        #endif
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    // Init GLAD
    #ifndef NDEBUG
    printf("Initalising GLAD.\n");
    #endif
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        #ifndef NDEBUG
        printf("Failed to initialize GLAD\n");
        #endif
        exit(-1);
    }

    // Set the GL viewport
    glViewport(0, 0, 800, 600);
    #ifndef NDEBUG
    printf("GLFW Window created.\n");
    #endif
    return window;
}