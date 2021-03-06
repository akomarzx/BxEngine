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

#ifdef _MSC_VER
#define _S_Assert assert(false)
#else
#include<iostream>
#define _S_Assert std::cout << "Compiled with non msvc"
#endif

struct BufferElements
{
	unsigned int m_Type;
	unsigned int m_Count;
	unsigned char m_Normalized;

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

class BufferLayout
{
	std::vector<BufferElements> m_Elements;
	unsigned int m_Stride;
public:
	BufferLayout()
		:m_Stride{ 0 } {}

	template<typename T>
	void Push(unsigned int count)
	{
		_S_Assert;
	}

	inline const auto& GetVectorElements()const { return m_Elements; }
	inline unsigned int GetStride()const { return m_Stride; }
};


template<>
inline void BufferLayout::Push<float>(unsigned int count)
{
	m_Elements.emplace_back(std::move(BufferElements{ GL_FLOAT , count , GL_FALSE }));
	m_Stride += BufferElements::GetSizeOfType(GL_FLOAT) * count;
}

template<>
inline void BufferLayout::Push<unsigned int>(unsigned int count)
{
	m_Elements.emplace_back(std::move(BufferElements{ GL_UNSIGNED_INT, count  , GL_TRUE }));
	m_Stride += BufferElements::GetSizeOfType(GL_UNSIGNED_INT) * count;
}
template<>
inline void BufferLayout::Push<unsigned char>(unsigned  int count)
{
	m_Elements.emplace_back(std::move(BufferElements{ GL_UNSIGNED_BYTE , count , GL_TRUE }));
	m_Stride += BufferElements::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}