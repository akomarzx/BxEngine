#pragma once
#include "VertexBuffer.h"
#include "BufferLayout.h"
class VertexArray
{
private:
	unsigned int m_VaoId;
public:
	VertexArray();
	~VertexArray();
	VertexArray(const VertexArray&) = delete;
	VertexArray(const VertexArray&&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
	void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout);
	void Bind()const;
	void UnBind()const;
};


