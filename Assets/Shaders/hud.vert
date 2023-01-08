#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 texCoord;


//out vec2 textureCoords;
out vec4 colors;

void main(void) {
	gl_Position = vec4(position, 1.0);
	//textureCoords = vec2((position.x+1.0)/2.0, 1 - (position.y+1.0)/2.0);
	colors = colour;
}