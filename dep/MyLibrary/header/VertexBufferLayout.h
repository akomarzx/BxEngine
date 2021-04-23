#pragma once
#include<vector>
#include<cassert>
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT  0x1406
#define GL_FALSE 0
#define GL_TRUE 1

struct VertexBufferElements
{
	unsigned int Type;
	unsigned int Count;
	unsigned char Normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: {return 4; }
		case GL_UNSIGNED_BYTE: {return 1; }
		case GL_UNSIGNED_INT: {return 4; }
		}
		assert(false);
	}
};

class VertexBufferLayout
{
	std::vector<VertexBufferElements> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		:m_Stride{ 0 } {}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT , count , GL_FALSE });
		m_Stride += VertexBufferElements::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count  , GL_TRUE });
		m_Stride += VertexBufferElements::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE , count , GL_TRUE});
		m_Stride += VertexBufferElements::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const auto& GetVectorElements()const { return m_Elements; }
	inline unsigned int GetStride()const { return m_Stride; }
};