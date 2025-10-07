// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow *window;

// GLM header file
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// shaders header file
#include <common/shader.hpp>

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

float delta = 0.0;

//--------------------------------------------------------------------------------
void transferDataToGPUMemory(void)
{
    // VAO
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("shaders/2Dflat.vert", "shaders/2Dflat.frag");

    static const GLfloat g_vertex_buffer_data[] = {
        0.0f,
        0.0f,
        0.0f,
        20.0f,
        0.0f,
        0.0f,
        20.0f,
        20.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        20.0f,
        20.0f,
        0.0f,
        0.0f,
        20.0f,
        0.0f,
        0.0f,
        20.0f,
        0.0f,
        20.0f,
        20.0f,
        0.0f,
        10.0f,
        30.0f,
        0.0f,

    };

    // One color for each vertex. They were generated randomly.
    static const GLfloat g_color_buffer_data[] = {
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
    };

    // Move vertex data to video memory; specifically to VBO called vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
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
void draw(void)
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    // create transformations
    // glm::mat4 model = glm::mat4(1.0f);
    // glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 mvp = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    // glm::mat4 mvp = projection * view * model;
    // Remember, matrix multiplication is the other way around

    // retrieve the matrix uniform locations
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

    glm::mat4 trans;
    trans = glm::translate(glm::mat4(1.0), glm::vec3(delta, delta, 0.0f));
    unsigned int m = glGetUniformLocation(programID, "trans");
    glUniformMatrix4fv(m, 1, GL_FALSE, &trans[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1,        // attribute. No particular reason for 1, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    // glEnable(GL_PROGRAM_POINT_SIZE);
    // glPointSize(10);
    //  Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 9); // 3 indices starting at 0 -> 1 triangle
    // glDrawArrays(GL_POINTS, 0, 9); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
//--------------------------------------------------------------------------------

int main(void)
{
    // Initialise GLFW
    glfwInit();

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window
    window = glfwCreateWindow(WindowWidth, WindowHeight, "Moving House in 2D ", NULL, NULL);

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

    // render scene for each frame
    do
    {
        // drawing callback
        draw();

        // Swap buffers
        glfwSwapBuffers(window);

        // looking for events
        glfwPollEvents();

        if (delta < 10)
            delta += 0.1;

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    // Cleanup VAO, VBOs, and shaders from GPU
    cleanupDataFromGPU();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
