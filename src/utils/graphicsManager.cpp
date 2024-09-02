#include "graphicsManager.h"

void GraphicsManager::genTextures(GLsizei n, GLuint* textures)
{
	glGenTextures(n, textures);
}

void GraphicsManager::bindTexture(GLenum target, GLuint texture)
{
	glBindTexture(target, texture);
}

void GraphicsManager::textureParameteri(GLenum target, GLenum pname, GLint param)
{
	glTexParameteri(target, pname, param);
}

void GraphicsManager::texImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data)
{
	glTexImage2D(target, level, internalformat, width, height, border, format, type, data);
}

void GraphicsManager::generateMipmap(GLenum target)
{
	glGenerateMipmap(target);
}

void GraphicsManager::drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
{
	glDrawElements(mode, count, type, indices);
}
