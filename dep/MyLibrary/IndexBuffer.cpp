#include"GL/glew.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int* Indices, unsigned int Count)
{
	glGenBuffers(1, &BufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Count, Indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &BufferId);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
