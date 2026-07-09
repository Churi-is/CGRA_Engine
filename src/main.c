#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

void exit_app(int code) {
    glfwTerminate();
    exit(code);
}

GLFWwindow* initialise_glfw_window() {
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
        exit_app(-1);
    }
    glfwMakeContextCurrent(window);

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        #ifndef NDEBUG
        printf("Failed to initialize GLAD\n");
        #endif
        exit_app(-1);
    }

    // Set the GL viewport
    glViewport(0, 0, 800, 600);
    return window;
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    #ifndef NDEBUG
    printf("You are Running a debug build.\n\n\n");
    #endif

    GLFWwindow* window = initialise_glfw_window();

    // Main glfw loop
    while(!glfwWindowShouldClose(window)){
        process_input(window);

        glClearColor(0.5f, 0.5, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    exit_app(0);
}