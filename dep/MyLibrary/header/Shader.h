#pragma once
#include<string>
#include<unordered_map>
struct m_ShaderSourceFiles
{
	std::string VertexShaderSrc;
	std::string FragmentShaderSrc;
};


class Shader
{
private:
	unsigned int m_ShaderId;
	m_ShaderSourceFiles ShaderSrcs;
	std::string m_FilePath;
	std::unordered_map<std::string, int>m_UniformCacheLocation;
public:
	Shader(std::string FileName);
	~Shader();
	Shader(const Shader&) = delete;
	Shader(const Shader&&) = delete;
	Shader& operator=(const Shader&) = delete;
	
	void Bind()const;
	void Unbind()const;
	void SetUniform1i(const char* name, int value);
	void SetUniform1f(const char* name, float value);
	void SetUniform4f(const char* name, float v0, float v1, float v2, float v3);
	inline unsigned int GetProgramId()const { return m_ShaderId; }

private:
	void ParseShaderSrc();
	unsigned int CompileShader(unsigned int type, const std::string& ShaderSrc);
	unsigned int CreateShader(const std::string& VertexShaderSrc, const std::string& FragmentShaderSrc);
	int GetUniformLocation(const std::string& Uniform_Name);

};