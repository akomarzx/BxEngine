#include"GL/glew.h"
#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"Shader.h"
#include"GDebugMessageCallBack.h"
Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Draw(const VertexBuffer& vbo, const IndexBuffer& ibo, const Shader& shader) const
{
	vbo.Bind();
	ibo.Bind();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Renderer::InitializeGLEW()
{
	if (glewInit() != GLEW_OK)
	{
		return false;
	}
	return true;
}

void Renderer::EnableGLEWDebugCallback()
{
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebugMessageCallback, nullptr);
}
