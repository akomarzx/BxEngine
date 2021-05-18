#pragma once
class VertexBuffer
{
private:
	unsigned int m_BufferId;
public:
	VertexBuffer(const float* Data, const unsigned int Size);
	~VertexBuffer();
	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer(const VertexBuffer&&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;

	void Bind()const;
	void UnBind()const;

	inline unsigned int GetBufferId()const { return m_BufferId; };
};

