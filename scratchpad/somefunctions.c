#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "render.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>


/*
Some generic functions I might use later when making this an actual engine.
*/


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