#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 TextureCoordinates;

out vec2 textureCoordinates;

void main () 
{
	textureCoordinates = TextureCoordinates;
	gl_Position = vec4(position, 1.0f);
}