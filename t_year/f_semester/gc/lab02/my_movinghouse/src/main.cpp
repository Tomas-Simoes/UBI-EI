#include <iostream>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../common/shader.hpp"

GLuint programID;
GLuint colorID;
GLuint mvpID;

GLuint get_square_buffer();
GLuint get_triangle_buffer();
std::vector<GLfloat> get_circle_buffer_data();

void draw_complete_house(glm::vec3 position, glm::vec3 scale);

void draw_window(glm::vec3 position, glm::vec3 scale);
void draw_house(glm::vec3 position, glm::vec3 scale);
void draw_door(glm::vec3 position, glm::vec3 scale);
void draw_roof(glm::vec3 position, glm::vec3 scale);
void draw_sun(glm::vec3 position, glm::vec3 scale);

void get_input_key(GLFWwindow *window);
bool window_toogle = true;
bool house_toogle = true;
bool roof_toogle = true;
bool door_toogle = true;
bool sun_pos = true;

bool b_prev = false;
bool r_prev = false;
bool w_prev = false;
bool d_prev = false;
bool s_prev = false;

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
    GLFWwindow *window = glfwCreateWindow(800, 800, "Moving house", NULL, NULL);
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

    // Load shaders
    programID = LoadShaders("shaders/2Dflat.vert", "shaders/2Dflat.frag");
    colorID = glGetUniformLocation(programID, "color_vec");
    mvpID = glGetUniformLocation(programID, "MVP");

    do
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader
        glUseProgram(programID);

        glEnableVertexAttribArray(0);

        get_input_key(window);

        glm::vec3 main_house_scale = glm::vec3(0.25f, 0.25f, 0.25f);
        draw_complete_house(glm::vec3(0.0f, 0.0f, 0.0f), main_house_scale);
        draw_complete_house(glm::vec3(-0.5f, -0.13f, 0.5f), main_house_scale * glm::vec3(0.25f, 0.25, 0.25f));
        draw_complete_house(glm::vec3(0.6f, 0.05f, 0.5f), main_house_scale * glm::vec3(1.25f, 1.25f, 1.25f));
        draw_sun(sun_pos ? glm::vec3(-0.75f, 0.75f, 0.0f) : glm::vec3(0.75f, 0.75f, 0.0f), glm::vec3(0.25f, 0.25f, 0.25f));

        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    // Cleanup VBO, shader, etc
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

GLuint get_square_buffer()
{
    static const GLfloat square_vertex_buffer_data[] = {
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f};

    GLuint square_vertex_buffer;
    glGenBuffers(1, &square_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, square_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertex_buffer_data), square_vertex_buffer_data, GL_STATIC_DRAW);

    return square_vertex_buffer;
}
GLuint get_triangle_buffer()
{
    static const GLfloat triangle_vertex_buffer_data[] = {
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f};

    GLuint triangle_vertex_buffer;
    glGenBuffers(1, &triangle_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertex_buffer_data), triangle_vertex_buffer_data, GL_STATIC_DRAW);

    return triangle_vertex_buffer;
}
std::vector<GLfloat> get_circle_buffer_data()
{
    float centerx = 0.0f;
    float centery = 0.0f;
    float radius = 1.0f;

    float iterations = 100;
    std::vector<GLfloat> circle_buffer_data;

    for (float i = 0; i < iterations; i++)
    {
        float theta = 2.0f * M_PI * i / iterations;
        float new_x = (centerx + radius * cos(theta));
        float new_y = (centery + radius * sin(theta));

        circle_buffer_data.push_back(new_x);
        circle_buffer_data.push_back(new_y);
        circle_buffer_data.push_back(0.0f);
    }

    return circle_buffer_data;
}

void draw_sun(glm::vec3 position, glm::vec3 scale)
{
    std::vector<GLfloat> vertex_buffer_data = get_circle_buffer_data();

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(GLfloat), vertex_buffer_data.data(), GL_STATIC_DRAW);

    glm::mat4 model = glm::translate(position) * glm::scale(scale);

    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &model[0][0]);
    glUniform3f(colorID, 1.0f, 1.0f, 0.0f); // yellow
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertex_buffer_data.size() / 3);
}

void draw_window(glm::vec3 position, glm::vec3 scale)
{
    GLuint vertex_buffer = get_square_buffer();

    glm::mat4 model = glm::translate(position) * glm::scale(scale);

    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &model[0][0]);
    glUniform3f(colorID, 0.0f, 0.0f, 0.5f); // blue
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_house(glm::vec3 position, glm::vec3 scale)
{
    GLuint vertex_buffer = get_square_buffer();

    glm::mat4 model = glm::translate(position) * glm::scale(scale);

    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &model[0][0]);
    glUniform3f(colorID, 1.0f, 0.0f, 0.0f); // red
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_roof(glm::vec3 position, glm::vec3 scale)
{
    GLuint vertex_buffer = get_triangle_buffer();

    glm::mat4 model = glm::translate(position) * glm::scale(scale) * glm::rotate(glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &model[0][0]);
    glUniform3f(colorID, 0.5f, 0.25f, 0.0f); // brown
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void draw_door(glm::vec3 position, glm::vec3 scale)
{
    GLuint vertex_buffer = get_square_buffer();

    glm::mat4 model = glm::translate(position) * glm::scale(scale);

    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &model[0][0]);
    glUniform3f(colorID, 0.5f, 0.0f, 0.0f); // dark red
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_complete_house(glm::vec3 position, glm::vec3 scale)
{
    if (house_toogle)
        draw_house(position + glm::vec3(0.0f, 0.0f, 0.0f) * scale, glm::vec3(0.75f, 0.75f, 0.75f) * scale);

    if (window_toogle)
    {
        draw_window(position + glm::vec3(-0.45f, 0.15f, 0.0f) * scale, glm::vec3(0.20f, 0.20f, 0.20f) * scale);
        draw_window(position + glm::vec3(0.45f, 0.15f, 0.0f) * scale, glm::vec3(0.20f, 0.20f, 0.20f) * scale);
    }

    if (door_toogle)
        draw_door(position + glm::vec3(0.0f, -0.55f, 0.0f) * scale, glm::vec3(0.1f, 0.20f, 0.20f) * scale);

    if (roof_toogle)
        draw_roof(position + glm::vec3(0.0f, 0.5f, 0.0f) * scale, glm::vec3(0.75f, 1.0f, 0.75f) * scale);
}

void get_input_key(GLFWwindow *window)
{
    bool b_curr = glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS;
    if (b_curr && !b_prev)
        house_toogle = !house_toogle;
    b_prev = b_curr;

    bool r_curr = glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;
    if (r_curr && !r_prev)
        roof_toogle = !roof_toogle;
    r_prev = r_curr;

    bool w_curr = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    if (w_curr && !w_prev)
        window_toogle = !window_toogle;
    w_prev = w_curr;

    bool d_curr = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    if (d_curr && !d_prev)
        door_toogle = !door_toogle;
    d_prev = d_curr;

    bool s_curr = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    if (s_curr && !s_prev)
        sun_pos = !sun_pos;
    s_prev = s_curr;
}
