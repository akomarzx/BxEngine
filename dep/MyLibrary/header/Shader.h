#pragma once
#include<string>

struct ShaderSourceFiles
{
	std::string VertexShaderSrc;
	std::string FragmentShaderSrc;
};


class Shader
{
private:
	unsigned int m_ShaderId;
	ShaderSourceFiles ShaderSrcs;
	
public:
	Shader();
	~Shader();
	Shader(const Shader&) = delete;
	Shader(const Shader&&) = delete;
	Shader& operator=(const Shader&) = delete;
	
	void Bind()const;
	void Unbind()const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	inline unsigned int GetProgramId()const { return m_ShaderId; }

private:
	void ParseShaderSrc();
	unsigned int CompileShader(unsigned int type, const std::string& ShaderSrc);
	unsigned int CreateShader(const std::string& VertexShaderSrc, const std::string& FragmentShaderSrc);
	int GetUniformLocation(const std::string& Uniform_Name);

};