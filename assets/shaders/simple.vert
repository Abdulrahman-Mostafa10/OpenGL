#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 vertex_color;

uniform float time;

void main(){
    gl_Position = vec4(position + vec3(sin(time), 0.0, 0.0), 1.0);
    vertex_color = color;
}