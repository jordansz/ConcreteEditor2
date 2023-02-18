#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec4 color;
layout(location = 3) in float tIndex;

uniform mat4 u_MVP;
//uniform float maxSquareHeight;
//uniform float maxSquareWidth;


out vec2 v_textCoord;
out float v_tIndex;
out vec4 v_color;

void main()
{
    v_color = color;
    gl_Position = u_MVP * position;
    v_textCoord = textCoord;
    v_tIndex = tIndex;
};
