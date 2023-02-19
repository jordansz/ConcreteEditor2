#version 330 core
out vec4 color;
in vec2 v_textCoord;
in float v_tIndex;
smooth in vec4 v_color;

uniform sampler2D u_Texture;
uniform int u_hasTexture;

void main()
{
    if(u_hasTexture == 0){
        color = v_color;
    }
    else if(u_hasTexture == 1)
        color = texture(u_Texture, v_textCoord);
};
