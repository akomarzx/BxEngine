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

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	float Vertices[]
	{
		-0.8f , 0.5f , 0.0f, 2.0f,
		 0.8f , 0.5f , 2.0f , 2.0f,
		-0.8f ,-0.5f, 0.0f , 0.0f,
		 0.8f , -0.5f ,2.0f , 0.0f
	};
	float TriangleWithColor[]
	{
		 0.0f ,  0.7f, 0.11f , 0.57f , 0.73f, 1.0f,// Vertex Position vec2 component & Color vec4
		-0.7f , -0.5f, 0.89f , 0.50f, 0.16f, 1.0f,
	 	 0.7f , -0.5f, 0.89f , 0.017f, 0.08f, 1.0f
	};

	unsigned int Indices[]
	{
		0,1,2,1,2,3
	};

	VertexArray vao1;
	VertexBuffer vbo1{Vertices , 4 * 4 * sizeof(float) };
	IndexBuffer ibo1{ Indices, 6 };
	BufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	vao1.AddBuffer(vbo1, layout);
	Shader shader1{ "BasicVertexShader.vert" , "BasicFragmentShader.frag"};
	shader1.Bind();
	Textures texture{ "pepe.jpg" };
	texture.Bind(0);
	shader1.SetUniform1i("U_Texture", 0);


	VertexArray vao2;
	VertexBuffer vbo2{ TriangleWithColor , 3 * 6 * sizeof(float) };
	IndexBuffer ibo2{ Indices , 3 };
	BufferLayout layout2;
	layout2.Push<float>(2);
	layout2.Push<float>(4);
	vao2.AddBuffer(vbo2, layout2);
	Shader shader2{ "ColorTriangle.vert" , "ColorTriangle.frag" };
	shader2.Bind();


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		renderer.Draw(vao1, ibo1, shader1);

		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}