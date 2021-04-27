#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include<iostream>
#include<string>
#include<cassert>
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include "VertexArray.h"
#include"GDebugMessageCallBack.h"
#include"Shader.h"
#include"Renderer.h"
#include"BxEngineConfig.h"


GLFWwindow* SetupGLFW(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	if (!glfwInit())
	{
		return nullptr;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	return glfwCreateWindow(width, height, title, monitor, share);
}

void EnableDebugMessageCallBack()
{
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebugMessageCallback, nullptr);
}

int main(int argc, char* argv[])
{
	std::cout << "Project: " << argv[0] << " Version " << BxEngine_VERSION_MAJOR << '.' << BxEngine_VERSION_MINOR << '\n';
	GLFWwindow* window;
	window = SetupGLFW(600, 500, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "NOT OK\n";
		glfwTerminate();
		return 1;
	}
	EnableDebugMessageCallBack();
	glfwSwapInterval(2);
	std::cout << glGetString(GL_VERSION) << '\n';

	float Positions[8]
	{
		 0.0f,	0.75f, //0
		-0.5f,  0.0f, //1
		 0.5f,  0.0f, //2
		 0.0f,	-0.75f //3
	};

	unsigned int Indices[]
	{
		0 , 1 , 2,
		1 , 2 , 3
	};
	VertexArray vao;
	VertexBufferLayout layout;
	VertexBuffer VBO1{ Positions , 4 * 2 * sizeof(float) };
	
	layout.Push<float>(2);
	
	vao.AddBuffer(VBO1, layout);
	
	IndexBuffer IBO1{ Indices , 6 };

	Shader ShaderProg;
	ShaderProg.Bind();
	
	ShaderProg.SetUniform4f("U_Color", 0.5f, 0.5f, 0.5f, 1.0f);

	Renderer renderer;
	float increment = 0.05f;
	float Red = 0.0f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		ShaderProg.SetUniform4f("U_Color", Red, 0.5f, 0.5f, 1.0f);
		
		renderer.Draw(VBO1, IBO1, ShaderProg);
		if (Red > 1.0f)
		{
			increment = -0.05f;
		}
		else if (Red < 0.0f)
		{
			increment = 0.05f;
		}
		Red += increment;
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
	
	return 0;
}