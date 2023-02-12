#version 330 core
out vec4 color;
in vec2 v_textCoord;
in float v_tIndex;
//in int ignorePix;
flat in vec4 v_color;

uniform sampler2D u_Texture;
uniform int u_hasTexture;

void main()
{
//    if(ignorePix == 1)
//        discard;
//    else if(u_hasTexture == 1 && v_color == vec4(0.0f, 1.0f, 1.0f, 0.5f))
//        color = v_color;
//     && v_color != vec4(0.0f, 1.0f, 1.0f, 0.5f)
    if(u_hasTexture == 1)
        color = texture(u_Texture, v_textCoord);
    else if(u_hasTexture == 0)
        color = v_color;
//    if(u_hasTexture == 1)
//        if(v_color == vec4(0.0f, 1.0f, 1.0f, 0.5f))
//            color = vec4(0.0f, 1.0f, 1.0f, 0.5f);
//        else
//            color = texture(u_Texture, v_textCoord);
//    else if(u_hasTexture == 0)
//        color = v_color;
};
