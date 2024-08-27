#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 vertexColor;

uniform vec3 testColor;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vertexColor = testColor; //vec3(0.0f, 2.0f, 0.0f); //testColor;
}