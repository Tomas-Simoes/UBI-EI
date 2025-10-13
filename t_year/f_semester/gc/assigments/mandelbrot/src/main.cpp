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

float vertexCount;
float delta = 0.0;

void hsvToRgb(float h, float s, float v, float &r, float &g, float &b);

//--------------------------------------------------------------------------------
struct MandelbrotData
{
    std::vector<GLfloat> mandelbrotBufferData;
    std::vector<GLfloat> colorBufferData;
};

MandelbrotData getMandelbrotData()
{
    int maxIterations = 1000;

    std::vector<GLfloat> maldebrotData = {};
    std::vector<GLfloat> colorData = {};

    for (float x = -1; x < 1; x += 0.01f)
    {
        for (float y = -1; y < 1; y += 0.01f)
        {
            float c_real = x * 2.0 - 0.5;
            float c_img = y * 2.0;
            float z_real = 0.0f;
            float z_img = 0.0f;

            int iteration = 0;

            while (iteration < maxIterations && (z_real * z_real + z_img * z_img) <= 4.0f)
            {
                float temp = (pow(z_real, 2) - pow(z_img, 2)) + c_real;
                z_img = (2 * z_real * z_img) + c_img;
                z_real = temp;

                iteration++;
            }

            maldebrotData.push_back(x);
            maldebrotData.push_back(y);
            maldebrotData.push_back(0.0f);

            if (iteration == maxIterations)
            {
                colorData.push_back(0.0f);
                colorData.push_back(0.0f);
                colorData.push_back(0.0f);
            }
            else
            {
                float hue = iteration * 10 % 360;
                float r, g, b;
                hsvToRgb(hue, 1.0f, 1.0f, r, g, b);

                colorData.push_back(r);
                colorData.push_back(g);
                colorData.push_back(b);
            }
        }
    }

    return {maldebrotData, colorData};
}

//--------------------------------------------------------------------------------
void transferDataToGPUMemory(void)
{
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    programID = LoadShaders("shaders/2Dflat.vert", "shaders/2Dflat.frag");

    auto [mandelbrotBufferData, colorBufferData] = getMandelbrotData();
    vertexCount = mandelbrotBufferData.size() / 3;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, mandelbrotBufferData.size() * sizeof(GLfloat), mandelbrotBufferData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, colorBufferData.size() * sizeof(GLfloat), colorBufferData.data(), GL_STATIC_DRAW);
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

    // glm::mat4 projection = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f);
    // glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), delta, glm::vec3(0.0f, 0.0f, 1.0f));

    // glm::mat4 mvp = projection * rotation;
    // unsigned int matrix = glGetUniformLocation(programID, "mvp");
    // glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

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

    glPointSize(2.0f);
    glDrawArrays(GL_POINTS, 0, vertexCount);

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
            delta += 0.01;
        else
            delta = 0.01;

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    cleanupDataFromGPU();
    glfwTerminate();

    return 0;
}

//--------------------------------------------------------------------------------

void hsvToRgb(float h, float s, float v, float &r, float &g, float &b)
{
    float c = v * s;
    float x = c * (1.0f - fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;

    float r1, g1, b1;

    if (h < 60)
    {
        r1 = c;
        g1 = x;
        b1 = 0;
    }
    else if (h < 120)
    {
        r1 = x;
        g1 = c;
        b1 = 0;
    }
    else if (h < 180)
    {
        r1 = 0;
        g1 = c;
        b1 = x;
    }
    else if (h < 240)
    {
        r1 = 0;
        g1 = x;
        b1 = c;
    }
    else if (h < 300)
    {
        r1 = x;
        g1 = 0;
        b1 = c;
    }
    else
    {
        r1 = c;
        g1 = 0;
        b1 = x;
    }

    r = r1 + m;
    g = g1 + m;
    b = b1 + m;
}