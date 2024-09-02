#pragma once

#include <iostream>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

class GraphicsManager
{
public:

	static void genTextures(GLsizei n, GLuint* textures);
	static void bindTexture(GLenum target, GLuint texture);
	static void textureParameteri(GLenum target, GLenum pname, GLint param);
	static void texImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data);
	static void generateMipmap(GLenum target);

	static void drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);
};
