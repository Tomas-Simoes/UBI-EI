// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// GLM header file
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// shaders header file
#include "common/shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Vertex array object (VAO)
GLuint VertexArrayID;

// Vertex buffer object (VBO)
GLuint vertexbuffer;

// color buffer object (CBO)
GLuint colorbuffer;

// GLSL program from the shaders
GLuint programID;


GLint WindowWidth = 800;
GLint WindowHeight = 800;

GLuint imageTexture;
GLuint quadVAO, quadVBO;

float delta = 0.0;

int mode = 0;              // 0 = original, 1 = roberts
int prevSpaceState = GLFW_RELEASE;

GLuint loadTexture(const char* filename)
{
    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data)
    {
        printf("Error loading image\n");
        return 0;
    }


    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return tex;
}


void transferDataToGPUMemory(void)
{
    // VAO
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("shaders/SimpleVertexShader.vertexshader",
                           "shaders/SimpleFragmentShader.fragmentshader");    
    
    float quadVertices[] = {
     // pos        // uv
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f,

        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    
}

//--------------------------------------------------------------------------------
void cleanupDataFromGPU()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
}

//--------------------------------------------------------------------------------
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, imageTexture);
    glUniform1i(glGetUniformLocation(programID, "uTex"), 0);

    glUniform1i(glGetUniformLocation(programID, "uMode"), mode);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
//--------------------------------------------------------------------------------



int main( void )
{
    // Initialise GLFW
    glfwInit();
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window
    window = glfwCreateWindow( WindowWidth, WindowHeight, "Moving House in 2D ", NULL, NULL);
    
    // Create window context
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    glewInit();
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    // transfer my data (vertices, colors, and shaders) to GPU side
    transferDataToGPUMemory();

    imageTexture = loadTexture("C:/Users/Utilizador/Desktop/Universidade-EI/3ANO/1Semestre/CG/pratical_projects/tp3/landscape.jpg");
    
    // render scene for each frame
    do{
        // drawing callback
        draw();
        
        // Swap buffers
        glfwSwapBuffers(window);
        
        // looking for events
        glfwPollEvents();

        int spaceState = glfwGetKey(window, GLFW_KEY_SPACE);
        if (spaceState == GLFW_PRESS && prevSpaceState == GLFW_RELEASE)
        {
            mode = 1 - mode; 
        }
        prevSpaceState = spaceState;
        
        if (delta < 10 )
            delta += 0.1;
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    
    // Cleanup VAO, VBOs, and shaders from GPU
    cleanupDataFromGPU();
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}