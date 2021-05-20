#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colors;

out vec4 v_colors;
void main()
{
    gl_Position = position;
    v_colors = colors;
}