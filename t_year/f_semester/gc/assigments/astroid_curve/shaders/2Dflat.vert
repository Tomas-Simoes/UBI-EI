#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 mvp; // this is your model matrix (or model-view-projection)

void main() {
    gl_Position = mvp * vec4(vertexPosition_modelspace, 1.0);
}
