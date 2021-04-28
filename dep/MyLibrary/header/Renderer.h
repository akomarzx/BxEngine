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
	
	void Draw(const VertexBuffer& vbo, const IndexBuffer& ibo, const Shader& shader)const;
	void Clear()const;

	static bool InitializeGLEW();
	static void EnableGLEWDebugCallback();
};