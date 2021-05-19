#Shader Vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
void main()
{
	v_TexCoord = texCoord;
	gl_Position = position;
}
	
	
#Shader Fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

uniform vec4 U_Color;
uniform sampler2D U_Texture;

void main()
{
	vec4 texColor = texture(U_Texture , v_TexCoord);
	color = texColor;
}