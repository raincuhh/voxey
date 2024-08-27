#include "block.h"


struct vertex {
	glm::vec3 position;
	glm::vec2 textureCoords;
};

const vertex cubeVertices[] = {

	// front
	{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f }}, // top right
	{{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f }}, // bottom right
	{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f }}, // bottom left
	{{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f }}, // top left

	// back
	{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f }}, // top right
	{{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f }}, // bottom right
	{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f }}, // bottom left
	{{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f }}, // top left

	// left
	{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f }}, // top right
	{{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f }}, // bottom right
	{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f }}, // bottom left
	{{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f }}, // top left

	// right
	{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f }}, // top right
	{{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f }}, // bottom right
	{{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f }}, // bottom left
	{{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f }}, // top left

	// top
	{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f }}, // top right
	{{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f }}, // bottom right
	{{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f }}, // bottom left
	{{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f }}, // top left

	// bottom
	{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f }}, // top right
	{{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f }}, // bottom right
	{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f }}, // bottom left
	{{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f }}, // top left
	
};

const unsigned int indices[] = {
	// front
	0, 1, 3, // triangle1 
	1, 2, 3, // triangle2 

	// back
	4, 7, 5, // triangle1 
	5, 7, 6, // triangle2 

	// left
	8, 11, 9, // triangle1 
	9, 11, 10, // triangle2 

	// right
	12, 13, 15, // triangle1 
	13, 14, 15, // triangle2 

	// top
	16, 17, 19, // triangle1 
	17, 18, 19, // triangle2 

	// bottom
	20, 23, 21, // triangle1
	21, 23, 22, // triangle2
	
};

Block::Block(BlockTypes type)
{
	setType(type);
	fragColorValue = inferBlockType(type);

	setupMesh();
	//currently renders some weird line strip texture
	setupTexture();
}

Block::~Block()
{
}

void Block::setType(BlockTypes type)
{
}

BlockTypes Block::getType() const
{
	return mBlockType;
}

void Block::draw([[maybe_unused]] unsigned int shaderProgram) const
{

	glBindTexture(GL_TEXTURE_2D, mTexture);

	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, sizeof(cubeVertices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}



void Block::setupMesh()
{
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);


	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	
	// localpos attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));//3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coords attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, textureCoords)); //(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Block::setupTexture()
{
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	unsigned char* textureData = stbi_load("assets/grassBlock/grassBlockFrontFace.png", &width, &height, &nrChannels, 0);
	
	if (textureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load texture " << std::endl; //change this to texture path in the future
	}

	stbi_image_free(textureData);
}


glm::vec3 Block::inferBlockType(BlockTypes type)
{
	switch (type)
	{
	case BlockTypeAir:
		return glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	case BlockTypeGrass:
		return glm::vec3(0.0f, 2.0f, 0.0f);
		break;
	case BlockTypeDirt:
		return glm::vec3(0.5f, 0.35f, 0.05f);
		break;
	case BlockTypeStone:
		return glm::vec3(0.7f, 0.7f, 0.7f);
		break;
	//case BlockTypeSand:
	//	return glm::vec3();
	//	break;
	//case BlockTypeWood:
	//	return glm::vec3();
	//	break;
	default:
		return glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	}
}
