#pragma once
#define APIENTRY __stdcall
typedef unsigned int GLenum;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef char GLchar;

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length,
	const GLchar* msg, const void* data);
