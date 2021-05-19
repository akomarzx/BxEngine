#include"GLFW/glfw3.h"
#include<iostream>
#include<string>
#include<cassert>
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include "VertexArray.h"
#include"Shader.h"
#include"Renderer.h"
#include"Texture.h"
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

int main(int argc, char** argv)
{
	std::cout << "Project: " << argv[0] << " Version " << BxEngine_VERSION_MAJOR << '.' << BxEngine_VERSION_MINOR << '\n';
	GLFWwindow* window;
	Renderer renderer;
	
	window = SetupGLFW(600, 500, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	if (!Renderer::InitializeGLEW())
	{
		std::cout << "NOT OK\n";
		glfwTerminate();
		return 1;
	}
	Renderer::EnableGLEWDebugCallback();
	glfwSwapInterval(2);
	std::cout << glGetString(GL_VERSION) << '\n';

	float Positions[]
	{
		 0.0f,	 0.75f, 0.0f, 0.0f, //0
		-0.5f,   0.0f , 1.0f, 0.0f,//1
		 0.5f,   0.0f , 1.0f, 1.0f, //2
		 0.0f,	-0.75f, 0.0f , 1.0f  //3
	};

	unsigned int Indices[]
	{
		0 , 1 , 2,
		1 , 2 , 3
	};
	VertexArray vao;
	BufferLayout layout;
	VertexBuffer VBO1{ Positions , 4 * 4 * sizeof(float) };

	layout.Push<float>(2);
	layout.Push<float>(2);
	
	vao.AddBuffer(VBO1, layout);

	IndexBuffer IBO1{ Indices , 6 };

	Shader ShaderProg("BasicShader.glsl");
	ShaderProg.Bind();
	Textures texture("concrete.jpg");
	texture.Bind();
	ShaderProg.SetUniform1i("U_Texture", 0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		renderer.Draw(vao, IBO1, ShaderProg);
		//glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}