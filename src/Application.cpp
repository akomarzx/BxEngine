#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<cassert>
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include "VertexArray.h"
#include"GDebugMessageCallBack.h"
#include"BxEngineConfig.h"

struct ShaderSourceFiles
{
    std::string VertexShaderSrc;
    std::string FragmentShaderSrc;
};

ShaderSourceFiles ParseShaderSrc()
{
	enum class ShaderType
	{
		Vertex = 0, Fragment = 1, NONE = 2
	};
    std::ifstream ShaderFile;
    std::stringstream ss[2];
    ShaderFile.open(ShaderSrcLocation, std::ifstream::in);
    ShaderType shadertype = ShaderType::NONE;
    if(ShaderFile.is_open())
    {
        //std::cout << "Successfully Opened\n";
        std::string line;
        while(std::getline(ShaderFile , line))
        {
            if(line.find("#Shader") != std::string::npos)
            {
                if(line.find("Vertex") != std::string::npos)
                {
                    shadertype = ShaderType::Vertex;
                }
                else
                {
                    shadertype = ShaderType::Fragment;
                }
            }
            else
            {
                ss[static_cast<int>(shadertype)] << line << '\n';
            }
        }
    }
    else{
        std::cout<<"Failed to Open Shader src File\n";
		return{ "" , "" };
    }
    ShaderFile.close();

    return {ss[0].str() , ss[1].str()};
}


static unsigned int CompileShader(unsigned int type, const std::string& ShaderSrc)
{
	unsigned int ShaderId = glCreateShader(type);
	const char* C_ShaderSrc = ShaderSrc.c_str();
	glShaderSource(ShaderId, 1, &C_ShaderSrc, nullptr);
	glCompileShader(ShaderId);

	int CompileStatus;
	glGetShaderiv(ShaderId, GL_COMPILE_STATUS , &CompileStatus);
	
	if (!CompileStatus)
	{
		int MessageLenght;
		glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &MessageLenght);
		char* MessageBuffer = (char*)alloca(MessageLenght * sizeof(char));
		glGetShaderInfoLog(ShaderId, MessageLenght, &MessageLenght, MessageBuffer);
		std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment" ) << " Shader failed to compile\n" << '\n';
		std::cout << MessageBuffer <<'\n';
		return 0;
	}
	
	return ShaderId;
}


static int CreateShader(const std::string& VertexShaderSrc , const std::string& FragmentShaderSrc)
{
	unsigned int Program = glCreateProgram();
	unsigned int VertexShader = CompileShader(GL_VERTEX_SHADER, VertexShaderSrc);
	unsigned int FragmentShader = CompileShader(GL_FRAGMENT_SHADER, FragmentShaderSrc);
	glAttachShader(Program, VertexShader);
	glAttachShader(Program, FragmentShader);
	glLinkProgram(Program);
	glValidateProgram(Program);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	return Program;
}


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

int main(int argc , char* argv[])
{

	std::cout << "Project: " << argv[0] <<" Version " <<BxEngine_VERSION_MAJOR << '.' << BxEngine_VERSION_MINOR << '\n';
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
	VertexBuffer VBO1{ Positions , 4 * 2 * sizeof(float)};
	layout.Push<float>(2);
	vao.AddBuffer(VBO1, layout);
	IndexBuffer IBO1{ Indices , 6 };
	ShaderSourceFiles shadersrc = ParseShaderSrc();
	unsigned int Shaders = CreateShader(shadersrc.VertexShaderSrc , shadersrc.FragmentShaderSrc);
	glUseProgram(Shaders);
	unsigned int UniformLocation = glGetUniformLocation(Shaders, "U_Color");
	assert(UniformLocation != -1);
	glUniform4f(UniformLocation, 0.5f, 0.5f, 0.5f, 1.0f);
	float increment = 0.05f;
	float Red = 0.0f;

	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glUniform4f(UniformLocation, Red, 0.5f, 0.5f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
	glDeleteProgram(Shaders);

	return 0;
}



