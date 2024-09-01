#include "graphicsManager.h"

GLFWwindow* GraphicsManager::createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
	if (!window)
	{
		std::cout << "error creating GLFW window" << std::endl;
		return nullptr;
	}
	else
	{
		std::cout << "created GLFW window" << std::endl;
		return window;
	}
}

int GraphicsManager::gladInit()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to init GLAD";
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "passed init GLAD" << std::endl;
		return EXIT_SUCCESS;
	}
}

int GraphicsManager::glfwInit()
{
	if (!::glfwInit())
	{
		std::cout << "failed to init GLFW" << std::endl;
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "passed init GLFW" << std::endl;
		return EXIT_SUCCESS;
	}
}

void GraphicsManager::windowHintInit()
{
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void GraphicsManager::pollEvents()
{
	glfwPollEvents();
}

void GraphicsManager::swapBuffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

bool GraphicsManager::shouldClose(GLFWwindow* window)
{
	return glfwWindowShouldClose(window);
}

void GraphicsManager::bufferSwapInterval(int interval)
{
	glfwSwapInterval(interval);
}

void GraphicsManager::enableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void GraphicsManager::setFrontFace(GLenum mode)
{
	glFrontFace(mode);
}

void GraphicsManager::setCullFace(GLenum mode)
{
	glCullFace(mode);
}

GLFWmonitor* GraphicsManager::getPrimaryMonitor()
{
	return glfwGetPrimaryMonitor();
}

const GLFWvidmode* GraphicsManager::getVideoMode(GLFWmonitor* monitor)
{
	return glfwGetVideoMode(monitor);
}

void GraphicsManager::setWindowPos(GLFWwindow* window, int xPos, int yPos)
{
	glfwSetWindowPos(window, xPos, yPos);
}

void GraphicsManager::setCurrentContext(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
}

void GraphicsManager::setFrameBufferCallback(GLFWwindow* window, GLFWframebuffersizefun callback)
{
	glfwSetFramebufferSizeCallback(window, callback);


}

void GraphicsManager::destroyWindow(GLFWwindow* window)
{
	glfwDestroyWindow(window);
}

void GraphicsManager::terminateGlfw()
{
	glfwTerminate();
}

double GraphicsManager::getTime()
{
	return glfwGetTime();
}

void GraphicsManager::genVertexArrays(GLsizei size, GLuint* arr)
{
	glGenVertexArrays(size, arr);
}

void GraphicsManager::bindVertexArray(GLuint arr)
{
	glBindVertexArray(arr);
}

void GraphicsManager::genBuffers(GLsizei size, GLuint* buffers)
{
	glGenBuffers(size, buffers);
}

void GraphicsManager::bindBuffer(GLenum target, GLuint buffer)
{
	glBindBuffer(target, buffer);
}

void GraphicsManager::bufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	glBufferData(target, size, data, usage);
}

void GraphicsManager::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void GraphicsManager::enableVertexAttribArray(GLuint index)
{
	glEnableVertexAttribArray(index);
}

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
