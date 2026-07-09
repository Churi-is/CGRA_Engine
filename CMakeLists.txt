cmake_minimum_required(VERSION 3.30)
project(CGRA_Engine C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

# ---------------------------------------------------------------------------
# GLFW - fetched from source and built if not already present on the system
# ---------------------------------------------------------------------------
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    TRUE
)

# Don't build GLFW's docs/tests/examples - we only want the library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# ---------------------------------------------------------------------------
# GLAD - OpenGL loader
# LearnOpenGL generates this per-project from https://glad.dav1d.de since it
# depends on which GL version/extensions you pick. Expected layout:
#   libs/glad/include/glad/glad.h
#   libs/glad/include/KHR/khrplatform.h
#   libs/glad/src/glad.c
# ---------------------------------------------------------------------------
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)

# ---------------------------------------------------------------------------
# System OpenGL
# ---------------------------------------------------------------------------
find_package(OpenGL REQUIRED)

# ---------------------------------------------------------------------------
# Main executable
# ---------------------------------------------------------------------------

### vvv My Code vvv
add_executable(${PROJECT_NAME} 
    src/main.c
    src/render/render.c
    src/window/window.c
    src/input/input.c
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /we4013 /we4028 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror=implicit-function-declaration)
endif()


target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
### ^^^ My Code ^^^

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad
    OpenGL::GL
)

if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl pthread)
endif()