#pragma once

#include <iostream>

#include "../../include/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

class GraphicsManager
{
public:

	static GLFWwindow* createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	static int gladInit();
	static int glfwInit();
	static void windowHintInit();
	static void pollEvents();
	static void swapBuffers(GLFWwindow* window);
	static bool shouldClose(GLFWwindow* window);

	static void bufferSwapInterval(int interval);
	static void enableDepthTest();
	static void setFrontFace(GLenum mode);
	static void setCullFace(GLenum mode);

	static GLFWmonitor* getPrimaryMonitor();
	static const GLFWvidmode* getVideoMode(GLFWmonitor* monitor);

	static void setWindowPos(GLFWwindow* window, int xPos, int yPos);
	static void setCurrentContext(GLFWwindow* window);
	static void setFrameBufferCallback(GLFWwindow* window, GLFWframebuffersizefun callback);

	static void destroyWindow(GLFWwindow* window);
	static void terminateGlfw();
	
	static double getTime();

	static void genVertexArrays(GLsizei size, GLuint* arr);
	static void bindVertexArray(GLuint arr);

	static void genBuffers(GLsizei size, GLuint* buffers);
	static void bindBuffer(GLenum target, GLuint buffer);
	static void bufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	static void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	static void enableVertexAttribArray(GLuint index);

	static void genTextures(GLsizei n, GLuint* textures);
	static void bindTexture(GLenum target, GLuint texture);
	static void textureParameteri(GLenum target, GLenum pname, GLint param);
	static void texImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data);
	static void generateMipmap(GLenum target);

	static void drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);
};
