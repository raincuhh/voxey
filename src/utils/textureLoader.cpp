#include "textureLoader.h"

int TextureLoader::LoadTexture(const std::string& filePath, unsigned int& texture)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width;
	int height;
	int nrChannels;
	unsigned char* texData = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

	if (!texData)
	{
		std::cout << "failed to load texture '" << filePath << "'";
		stbi_image_free(texData);
		return 0;
	}
	else
	{
		GLenum format = 
			(nrChannels == 1) ? GL_RED :
			(nrChannels == 3) ? GL_RGB :
			(nrChannels == 4) ? GL_RGBA : GL_RGB;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(texData);
	}
	return 1;
}
