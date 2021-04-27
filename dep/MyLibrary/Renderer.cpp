#include"GL/glew.h"
#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"Shader.h"
Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Draw(const VertexBuffer& vbo, const IndexBuffer& ibo, const Shader& shader)
{
	vbo.Bind();
	ibo.Bind();
	shader.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}