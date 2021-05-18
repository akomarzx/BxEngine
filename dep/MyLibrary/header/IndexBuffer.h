#pragma once
class IndexBuffer
{
private:
	unsigned int m_BufferId;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* Indices, const unsigned int Count);
	~IndexBuffer();
	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer(const IndexBuffer&&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;

	void Bind()const;
	void UnBind()const;

	inline unsigned int GetBufferId()const { return m_BufferId; };
	inline unsigned GetCount() const { return m_Count; }
};

