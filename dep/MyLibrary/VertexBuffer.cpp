#include"GL/glew.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const float* Data, const unsigned int Size)
{
	glGenBuffers(1, &m_BufferId); // Generate a Buffer of Memory
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferId); // Selecting of Binding a memory to work with.
	glBufferData(GL_ARRAY_BUFFER, Size , Data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_BufferId);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER , 0);
}
