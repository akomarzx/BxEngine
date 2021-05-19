#include"GL/glew.h"
#include"Texture.h"
#include"stb_image.h"
#include"BxEngineConfig.h"

Textures::Textures(const std::string TextureName)
	:m_Filepath{TextureLocation + TextureName} , 
	m_Buffer {nullptr},
	m_widgth{0},
	m_Height{0},
	m_BPP{0}
{
	glGenTextures(1, &m_RendererId);
	glBindTexture(GL_TEXTURE_2D, m_RendererId);

	stbi_set_flip_vertically_on_load(1);

	m_Buffer = stbi_load(m_Filepath.c_str(), &m_widgth, &m_Height, &m_BPP, 4);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_widgth, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_Buffer)
	{
		stbi_image_free(m_Buffer);
	}
}

Textures::~Textures()
{
	glDeleteTextures(1, &m_RendererId);
}

void Textures::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererId);

}

void Textures::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);

}
