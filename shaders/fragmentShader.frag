#version 330 core
out vec4 FragColor;

in vec2 textureCoord;

uniform vec3 uniformFragColor;
uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, textureCoord); 
} 