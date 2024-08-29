#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoord;

out vec2 textureCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

vec3 testPos = vec3(0.0f, 0.0f, 1.0f);

void main()
{
	gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
	textureCoord = aTextureCoord;
}