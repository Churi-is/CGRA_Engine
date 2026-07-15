#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "render.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>


unsigned int generate_texture(char* assetPath) {
    stbi_set_flip_vertically_on_load(1); // tell stb_image.h to flip loaded texture's on the y-axis.
    
    unsigned int textureID;
    
    // set texture ID and register it.
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID); 

     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmapsSS
    int width, height, nrChannels;
    unsigned char *data = stbi_load(assetPath, &width, &height, &nrChannels, 0);
    if (data) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, nrChannels-1); // IDK if minus 1 is right or nr channels isnt what i think it is
        glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
        glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, height);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Failed to load texture. [%s] :(", assetPath);
    }
    stbi_image_free(data);

    return textureID;
}

Object render_initialise(){
    #ifndef NDEBUG
    printf("Initalising OpenGL Buffers.\n");
    #endif

    // verts and indices
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int texture1 = generate_texture("./assets/container.jpg");
    unsigned int texture2 = generate_texture("./assets/dadripzoom.jpg");

    Mesh mesh = render_create_mesh(vertices, sizeof(vertices), indices, sizeof(indices));
    
    // assemble shader
    Shader s = shader_create_from_paths("./src/render/shaders/vert.glsl", "./src/render/shaders/frag.glsl");

    shader_use(s);
    shader_set_int(s,"texture1", 0);
    shader_set_int(s,"texture2", 1); // maybe makes more sense to store the texture in the shader, rather than the object?

    Object o = {.mesh=mesh, .s=s, .texture1ID=texture1, .texture2ID=texture2}; // need another way to hold arbitrary ammounts of textures.
    return o;
}

// NOTE: could have a output pointer as parameter, save the copying for larger meshes.
// Also many magic numbers that need params or to be dirived from elsewhere
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

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    Mesh m = {.VAO=VAO, .EBO=EBO, .VBO=VBO};
    return m;
}

void render_frame(Object* o) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, o->texture1ID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, o->texture2ID);


    shader_use(o->s);

    glBindVertexArray(o->mesh.VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}