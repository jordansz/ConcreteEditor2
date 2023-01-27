#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec4 color;
layout(location = 3) in float tIndex;
//layout(location = 4) in float maxSquareHeight;
//layout(location = 5) in float maxSquareWidth;

uniform mat4 u_MVP;

out vec2 v_textCoord;
out float v_tIndex;
out vec4 v_color;

void main()
{
    v_color = color;
    //   if(tIndex == 0 &&
    //     (position >= abs(maxSquareWidth) || position >= abs(maxSquareHeight)))){
    //        discard;
    //   }
//    else{
//        gl_Position = u_MVP * position;
//    }
   gl_Position = u_MVP * position;
//   if(tIndex == 0 &&
//     (gl_Position >= abs(maxSquareWidth) || gl_Position >= abs(maxSquareHeight)))){
//        v_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);     //completly transparent
//   }
   v_textCoord = textCoord;
   v_color = color;
   v_tIndex = tIndex;
};
