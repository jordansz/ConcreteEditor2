#version 330 core
out vec4 color;
in vec2 v_textCoord;
in float v_tIndex;
in vec4 v_color;

uniform sampler2D u_Texture;

void main()
{
    if(v_tIndex == 1){
        color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
    else if(v_tIndex == 0){
        color = texture(u_Texture, v_textCoord);
//        color = vec4(1.0f, 0.0f, 0.0f, 0.5f);
    }
//    else{
//        color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
//    }
//    else{
//        color = texture(u_Texture, v_textCoord);
//    }
//    color = v_color;
};
