#Shader Vertex
#version 330 core

layout(location = 0) in vec4 position;
void main()
{
	gl_Position = position;
}
	
	
#Shader Fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 U_Color;
void main()
{
	color = U_Color;
}