#version 330 core
out vec4 color;
in vec2 v_textCoord;
in float v_tIndex;
flat in vec4 v_color;

uniform sampler2D u_Texture;

void main()
{
    if(v_tIndex == 1){
        color = v_color;
    }
    else if(v_tIndex == 0){
        color = texture(u_Texture, v_textCoord);
    }
};
