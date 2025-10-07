// include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>    // GLEW include
#include <GLFW/glfw3.h> // GLFW include
GLFWwindow *window;
#include <glm/glm.hpp> // GLM include

using namespace glm;
int main(void)
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(400, 400, "Window in blue", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window \n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        // Draw nothing…
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
}
