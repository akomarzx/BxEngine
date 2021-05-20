#include"GL/glew.h"
#include "Shader.h"
#include <sstream>
#include<iostream>
#include<fstream>
#include"BxEngineConfig.h"

Shader::Shader(std::string VertexShaderFilename , std::string FragmentShaderFilename)
	:m_VertexShaderFilePath{ShaderSrcLocation + VertexShaderFilename} , m_FragmentShaderFilePath{ShaderSrcLocation + FragmentShaderFilename}
{
	ParseShaderSrc(ShaderType::Vertex);
	ParseShaderSrc(ShaderType::Fragment);
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

void Shader::SetUniform1i(const char* name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const char* name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const char* name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0 , v1 , v2, v3);
}

void Shader::ParseShaderSrc(ShaderType type)
{
	const char* shadersrc;
	if (type == ShaderType::Vertex)
	{
		shadersrc = m_VertexShaderFilePath.c_str();
	}
	else
	{
		shadersrc = m_FragmentShaderFilePath.c_str();
	}
	std::ifstream ShaderFile;
	std::stringstream ss;
	ShaderFile.open(shadersrc, std::ifstream::in);
	if (ShaderFile.is_open())
	{
		//std::cout << "Successfully Opened\n";
		std::string line;
		while (std::getline(ShaderFile, line))
		{
			ss << line << '\n';
		}
	}
	else {
		std::cout << "Failed to Open Shader src File\n";
		throw;
	}
	ShaderFile.close();
	std::string *src = (std::string*)&ShaderSrcs;
	src[(int)type] = ss.str();
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
		int MessageLength;
		glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &MessageLength);
		char* MessageBuffer = (char*)alloca(MessageLength * sizeof(char));
		glGetShaderInfoLog(ShaderId, MessageLength, &MessageLength, MessageBuffer);
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
	if (m_UniformCacheLocation.find(Uniform_Name) != m_UniformCacheLocation.end())
	{
		return m_UniformCacheLocation[Uniform_Name];
	}

	int Location = glGetUniformLocation(m_ShaderId, Uniform_Name.c_str());
	if (Location == -1)
	{
		std::cout << "Warning Uniform " << Uniform_Name << " not found\n";
		//throw std::runtime_error ("Uniform Not Found!");
	}
	m_UniformCacheLocation.emplace(Uniform_Name, Location);
	return m_UniformCacheLocation[Uniform_Name];
}
