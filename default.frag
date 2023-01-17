#version 330 core
out vec4 color;
in vec2 v_textCoord;
in float t_index;
in vec4 v_color;

uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_textCoord);
//    color = v_color;
};
