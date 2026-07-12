#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "render/render.h"
#include "window/window.h"
#include "input/input.h"
#include "render/shader.h"

int main()
{
    #ifndef NDEBUG
    printf("You are Running a debug build.\n\n\n");
    #endif

    char path[]  = "./src/main.c";
    shader_create_from_paths(path, path);

    GLFWwindow* window = window_init();
    Object state = render_initialise();

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