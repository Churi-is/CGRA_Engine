#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "render/render.h"
#include "render/window.h"
#include "input/input.h"

int main()
{
    #ifndef NDEBUG
    printf("You are Running a debug build.\n\n\n");
    #endif

    GLFWwindow* window = initialise_glfw_window();

    // Main glfw loop
    while(!glfwWindowShouldClose(window)){
        process_input(window);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    exit_app(0);
}