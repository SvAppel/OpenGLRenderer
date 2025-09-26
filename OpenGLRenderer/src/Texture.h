#pragma once
#include "TriangleRenderer.h"

class Texture 
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height;
	//Byte per Pixel
	int m_BPP;

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0);
	void Unbind();

	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }
};