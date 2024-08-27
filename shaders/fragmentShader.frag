#version 330 core
out vec4 FragColor;

uniform vec3 uniformFragColor;
//in vec3 vertexColor;

void main()
{
    FragColor = vec4(uniformFragColor.xyz, 1.0f); //vec4(1.0f, 0.0f, 0.0f, 1.0f);
} 