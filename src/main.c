#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "render/render.h"
#include "window/window.h"
#include "input/input.h"

int main()
{
    #ifndef NDEBUG
    printf("You are Running a debug build.\n\n\n");
    #endif

    GLFWwindow* window = window_init();
    RenderState state = render_initialise();

    // Main glfw loop
    while(!glfwWindowShouldClose(window)){
        input_process(window);

        render_frame(&state);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    window_destroy();
    return 0;
}