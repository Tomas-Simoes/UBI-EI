#version 330 core
out vec3 color;
uniform vec3 color_vec;

void main() {
    color = color_vec;
}
