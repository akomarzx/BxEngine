#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;


uniform sampler2D U_Texture;

void main()
{
	vec4 texColor = texture(U_Texture , v_TexCoord);
	color = texColor;
}