#version 330 core 

layout(location = 0) out vec4 o_Color;


in vec4 v_Color;  
in vec2 v_TexCoord;  

uniform sampler2D u_Texture1;

void main() 
{ 
	o_Color = texture(u_Texture1, v_TexCoord) * v_Color;
};