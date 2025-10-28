#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../common/shader.hpp"
#include <cmath>
#include <vector>

using namespace glm;

GLFWwindow *window;

GLuint VertexArrayID;

GLuint vertexbuffer;
GLuint colorbuffer;

GLuint programID;

GLint WindowWidth = 800;
GLint WindowHeight = 800;

float delta = 0.0;

//--------------------------------------------------------------------------------
std::vector<GLfloat> getAstroidCurveData()
{
    int constant = 10;
    int iterations = 1000;
    std::vector<GLfloat> astroidCurveData = {};

    for (int t = 0; t < iterations; t++)
    {
        // Use a proper parameter range for the astroid curve (0 to 2*PI)
        float param = (t / (float)iterations) * 2.0f * M_PI;

        float x = constant * pow(cos(param), 3);
        float y = constant * pow(sin(param), 3);

        astroidCurveData.push_back(x);
        astroidCurveData.push_back(y);
        astroidCurveData.push_back(0.0f);
    }

    return astroidCurveData;
}

std::vector<GLfloat> getColorData()
{
    std::vector<GLfloat> colorData = {};

    for (int i = 0; i < 1000; i++)
    {
        colorData.push_back(rand() % 100 / 100.0f); // R
        colorData.push_back(rand() % 100 / 100.0f); // G
        colorData.push_back(rand() % 100 / 100.0f); // B
    }

    return colorData;
}

//--------------------------------------------------------------------------------
void transferDataToGPUMemory(void)
{
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    programID = LoadShaders("shaders/2Dflat.vert", "shaders/2Dflat.frag");

    std::vector<GLfloat> astroid_curve_buffer_data = getAstroidCurveData();
    std::vector<GLfloat> color_buffer_data = getColorData();

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, astroid_curve_buffer_data.size() * sizeof(GLfloat), astroid_curve_buffer_data.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() * sizeof(GLfloat), color_buffer_data.data(), GL_STATIC_DRAW);
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
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programID);

    glm::mat4 projection = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f);
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), delta, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 mvp = projection * rotation;
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

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

    glLineWidth(10.0f);

    glDrawArrays(GL_LINE_LOOP, 0, 1000);

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
            delta += 0.5;
        else
            delta = 0.01;

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    cleanupDataFromGPU();
    glfwTerminate();

    return 0;
}