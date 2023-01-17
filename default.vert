#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec4 color;

uniform mat4 u_MVP;

out vec2 v_textCoord;
out float t_index;
out vec4 v_color;

void main()
{
   gl_Position = u_MVP * position;
   v_textCoord = textCoord;
   v_color = color;
};
