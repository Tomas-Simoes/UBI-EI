#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../common/shader.hpp"

int main()
{
    // Initialise GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Request OpenGL 3.3 core profile
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MacOS; harmless elsewhere
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(800, 600, "First Triangle", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to open GLFW window.\n";
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // needed in core profile
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Set background color
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    // Vertex Array Object
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // if you move the center or want a radius bigger than one, be careful for the normalization
    float centerx = 0.0f;
    float centery = 0.0f;

    float radiusx = 1.2f;
    float radiusy = 0.8f;

    float iterations = 100;
    std::vector<GLfloat> circle_buffer_data;
    std::vector<GLfloat> rand_point_buffer_data;

    for (float i = 0; i < iterations; i++)
    {
        float theta = 2.0f * M_PI * i / iterations;
        float new_x = (centerx + radiusx * cos(theta));
        float new_y = (centery + radiusy * sin(theta));

        float rho = sqrt((double)rand() / RAND_MAX);
        float phi = sqrt((double)rand() * 2 * M_PI);
        float random_x = centerx + radiusx * rho * cos(phi);
        float random_y = centery + radiusy * rho * sin(phi);

        circle_buffer_data.push_back(new_x);
        circle_buffer_data.push_back(new_y);
        circle_buffer_data.push_back(0.0f);

        rand_point_buffer_data.push_back(random_x);
        rand_point_buffer_data.push_back(random_y);
        rand_point_buffer_data.push_back(0.0f);
    }

    // green Vertex buffer
    GLuint circle_vertex_buffer;
    glGenBuffers(1, &circle_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, circle_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, circle_buffer_data.size() * sizeof(GLfloat), circle_buffer_data.data(), GL_STATIC_DRAW);

    GLuint rand_points_vertex_buffer;
    glGenBuffers(1, &rand_points_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, rand_points_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, rand_point_buffer_data.size() * sizeof(GLfloat), rand_point_buffer_data.data(), GL_STATIC_DRAW);

    // Load shaders
    GLuint programID = LoadShaders("shaders/2Dflat.vert", "shaders/2Dflat.frag");
    GLuint colorID = glGetUniformLocation(programID, "colorVec");

    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader
        glUseProgram(programID);

        glEnableVertexAttribArray(0);

        glUniform3f(colorID, 1.0f, 0.0f, 0.0f); // red
        glBindBuffer(GL_ARRAY_BUFFER, circle_vertex_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glDrawArrays(GL_LINE_LOOP, 0, circle_buffer_data.size() / 3);

        float num_triangles = (rand_point_buffer_data.size() / 3) - (rand_point_buffer_data.size() / 3) % 3;
        for (int i = 0; i < num_triangles; i++)
        {
            float r = (float)rand() / RAND_MAX;
            float g = (float)rand() / RAND_MAX;
            float b = (float)rand() / RAND_MAX;

            glUniform3f(colorID, r, g, b); // random color
            glBindBuffer(GL_ARRAY_BUFFER, rand_points_vertex_buffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
            glDrawArrays(GL_TRIANGLES, i, 3);
        }

        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    // Cleanup VBO, shader, etc
    glDeleteBuffers(1, &circle_vertex_buffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
