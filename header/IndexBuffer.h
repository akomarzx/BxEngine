#pragma once
class IndexBuffer
{
private:
	unsigned int BufferId;
public:
	IndexBuffer(unsigned int* Indices, unsigned int Count);
	~IndexBuffer();
	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer(const IndexBuffer&&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;

	void Bind()const;
	void UnBind()const;

	inline unsigned int GetBufferId()const { return BufferId; };
};

