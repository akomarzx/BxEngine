#pragma once
class VertexBuffer
{
private:
	unsigned int BufferId;
public:
	VertexBuffer(float* Data, unsigned int Size);
	~VertexBuffer();
	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer(const VertexBuffer&&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;

	void Bind()const;
	void UnBind()const;

	inline unsigned int GetBufferId()const { return BufferId; };
};

