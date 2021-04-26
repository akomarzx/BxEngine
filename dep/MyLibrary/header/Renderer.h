#pragma once

class VertexBuffer;
class IndexBuffer;
class Shader;

class Renderer
{
public:
	Renderer();
	~Renderer();

	Renderer(const Renderer&) = delete;
	Renderer(const Renderer&&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	
	void Draw()
};