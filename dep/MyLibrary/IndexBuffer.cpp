#include"GL/glew.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* Indices, const unsigned int Count)
	:m_Count{ Count }
{
	glGenBuffers(1, &m_BufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Count, Indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_BufferId);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

