#version 330 core

in vec2 textureCoord;

out vec4 FragColor;

uniform vec3 uniformFragColor;
uniform sampler2D aTexture;

void main()
{
    FragColor = texture(aTexture, textureCoord); 
} 