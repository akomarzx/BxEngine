#pragma once
#include<string>
class Textures
{
private:
	unsigned int m_RendererId;
	std::string m_Filepath;
	unsigned char* m_Buffer;//Buffer for the texture
	int m_widgth, m_Height, m_BPP;// BPP = Bits per Pixel
public:
	Textures(const std::string TextureName);
	~Textures();
	
	void Bind(unsigned int slot = 0)const;
	void UnBind()const;

	inline const int GetWidgth()const { return m_widgth; }
	inline const int GetHeight()const { return m_Height; }
};