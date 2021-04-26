#include"GL/glew.h"
#include "Shader.h"
#include <sstream>
#include<iostream>
#include<fstream>
#include"BxEngineConfig.h"

Shader::Shader()
{
	ParseShaderSrc();
	m_ShaderId = CreateShader(ShaderSrcs.VertexShaderSrc, ShaderSrcs.FragmentShaderSrc);
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderId);
}

void Shader::Bind() const
{
	glUseProgram(m_ShaderId);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0 , v1 , v2, v3);
}

void Shader::ParseShaderSrc()
{
	enum class ShaderType
	{
		Vertex = 0, Fragment = 1, NONE = 2
	};
	std::ifstream ShaderFile;
	std::stringstream ss[2];
	ShaderFile.open(ShaderSrcLocation, std::ifstream::in);
	ShaderType shadertype = ShaderType::NONE;
	if (ShaderFile.is_open())
	{
		//std::cout << "Successfully Opened\n";
		std::string line;
		while (std::getline(ShaderFile, line))
		{
			if (line.find("#Shader") != std::string::npos)
			{
				if (line.find("Vertex") != std::string::npos)
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
	else {
		std::cout << "Failed to Open Shader src File\n";
		throw;
	}
	ShaderFile.close();

	ShaderSrcs = { ss[0].str() , ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& ShaderSrc)
{
	unsigned int ShaderId = glCreateShader(type);
	const char* C_ShaderSrc = ShaderSrc.c_str();
	glShaderSource(ShaderId, 1, &C_ShaderSrc, nullptr);
	glCompileShader(ShaderId);

	int CompileStatus;
	glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &CompileStatus);

	if (!CompileStatus)
	{
		int MessageLenght;
		glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &MessageLenght);
		char* MessageBuffer = (char*)alloca(MessageLenght * sizeof(char));
		glGetShaderInfoLog(ShaderId, MessageLenght, &MessageLenght, MessageBuffer);
		std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader failed to compile\n" << '\n';
		std::cout << MessageBuffer << '\n';
		return 0;
	}

	return ShaderId;
}

unsigned int Shader::CreateShader(const std::string& VertexShaderSrc, const std::string& FragmentShaderSrc)
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

int Shader::GetUniformLocation(const std::string& Uniform_Name)
{
	int Location = glGetUniformLocation(m_ShaderId, Uniform_Name.c_str());
	if (Location == -1)
	{
		std::cout << "Warning Uniform " << Uniform_Name << " not found\n";
		throw std::runtime_error ("Uniform Not Found!");
	}
	return Location;
}