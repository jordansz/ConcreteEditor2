#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec4 color;
layout(location = 3) in float tIndex;

uniform mat4 u_MVP;
uniform float maxSquareHeight;
uniform float maxSquareWidth;

out vec2 v_textCoord;
out float v_tIndex;
//out int ignorePix;
flat out vec4 v_color;

void main()
{
//    if(tIndex == 1.0f && ((abs(position.x) > maxSquareWidth) || (abs(position.y) > maxSquareHeight))
//            || position.z > -1.0f){
//        v_color = vec4(0.0f, 1.0f, 1.0f, 0.5f);
//    }
//    else{
//        v_color = color;
//    }
    v_color = color;
    gl_Position = u_MVP * position;
    v_textCoord = textCoord;
    v_tIndex = tIndex;
//    if(tIndex == 1.0f && (abs(gl_Position.x) > maxSquareWidth) || (abs(gl_Position.y) > maxSquareHeight)){
//        v_color = vec4(0.0f, 1.0f, 1.0f, 0.5f);
//    }
//    else
//        v_color = color;
};
