#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#include "../common/shader.hpp"

using namespace glm;

GLFWwindow *window;

GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint texcoordbuffer;
GLuint texture;

GLuint programID;

GLint WindowWidth = 800;
GLint WindowHeight = 800;

unsigned char *image_data = NULL;
unsigned char *filtered_data = NULL;
int img_width, img_height, img_channels;

//--------------------------------------------------------------------------------
// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(unsigned char*)a - *(unsigned char*)b);
}

//--------------------------------------------------------------------------------
// Apply median filter to image
void median_filter(unsigned char *input, unsigned char *output, int width, int height, int channels, int kernel_size) {
    int half_kernel = kernel_size / 2;
    int kernel_area = kernel_size * kernel_size;
    unsigned char *window = (unsigned char*)malloc(kernel_area * sizeof(unsigned char));
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channels; c++) {
                int count = 0;
                
                // Collect pixel values in the kernel window
                for (int ky = -half_kernel; ky <= half_kernel; ky++) {
                    for (int kx = -half_kernel; kx <= half_kernel; kx++) {
                        int ny = y + ky;
                        int nx = x + kx;
                        
                        // Clamp to image boundaries
                        if (nx < 0) nx = 0;
                        if (nx >= width) nx = width - 1;
                        if (ny < 0) ny = 0;
                        if (ny >= height) ny = height - 1;
                        
                        window[count++] = input[(ny * width + nx) * channels + c];
                    }
                }
                
                // Sort and get median
                qsort(window, kernel_area, sizeof(unsigned char), compare);
                output[(y * width + x) * channels + c] = window[kernel_area / 2];
            }
        }
    }
    
    free(window);
}

//--------------------------------------------------------------------------------
void loadAndFilterImage(const char *filename)
{
    // Don't flip - keep original orientation
    stbi_set_flip_vertically_on_load(0);
    
    // Force 3 channels (RGB) to avoid issues
    image_data = stbi_load(filename, &img_width, &img_height, &img_channels, 3);
    if (!image_data) {
        printf("Failed to load image: %s\n", filename);
        exit(1);
    }
    
    img_channels = 3; // We forced RGB
    printf("Loaded image: %dx%d with %d channels\n", img_width, img_height, img_channels);
    
    // Allocate memory for filtered image
    filtered_data = (unsigned char*)malloc(img_width * img_height * img_channels);
    
    // Apply median filter (3x3 kernel)
    printf("Applying median filter...\n");
    median_filter(image_data, filtered_data, img_width, img_height, img_channels, 3);
    printf("Filtering complete!\n");
}

//--------------------------------------------------------------------------------
void transferDataToGPUMemory(void)
{
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    programID = LoadShaders("shaders/texture.vert", "shaders/texture.frag");

    // Quad vertices (two triangles forming a rectangle)
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f
    };

    // Texture coordinates (fixed - no flip needed)
    GLfloat texcoords[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };

    // Upload vertex data
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Upload texture coordinate data
    glGenBuffers(1, &texcoordbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texcoordbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

    // Create and configure texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    // Upload filtered image to GPU (always RGB now)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, filtered_data);
    
    // Check for OpenGL errors
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("OpenGL Error: %d\n", err);
    }
}

//--------------------------------------------------------------------------------
void cleanupDataFromGPU()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &texcoordbuffer);
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
    
    if (image_data) stbi_image_free(image_data);
    if (filtered_data) free(filtered_data);
}

//--------------------------------------------------------------------------------
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programID);

    // Set up MVP matrix with proper aspect ratio
    float aspect = (float)img_width / (float)img_height;
    glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;
    
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(programID, "textureSampler"), 0);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // Texture coordinates
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, texcoordbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // Draw the quad
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

//--------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    // Load and filter the image
    loadAndFilterImage(argv[1]);

    // Initialise GLFW
    glfwInit();

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window
    window = glfwCreateWindow(WindowWidth, WindowHeight, "Median Filter Demo", NULL, NULL);

    // Create window context
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true;
    glewInit();

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Transfer data to GPU
    transferDataToGPUMemory();

    // Render scene for each frame
    do
    {
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    } 
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    cleanupDataFromGPU();
    glfwTerminate();

    return 0;
}