#include"GL/glew.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VaoId);
	glBindVertexArray(m_VaoId);
}

VertexArray::~VertexArray()
{ 
	glDeleteVertexArrays(1, &m_VaoId);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const BufferLayout& layout)
{
	vb.Bind();
	auto const& BufferLayoutElements = layout.GetVectorElements();
	unsigned int Offset{ 0 };
	for (size_t i{ 0 }; i < BufferLayoutElements.size(); ++i)
	{
		const auto& LayoutElement = BufferLayoutElements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, LayoutElement.Count, LayoutElement.Type , LayoutElement.Normalized,
								layout.GetStride(), (const void*)Offset);
		Offset += LayoutElement.Count * BufferElements::GetSizeOfType(LayoutElement.Type);
 	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_VaoId);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
