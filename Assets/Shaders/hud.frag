#version 400 core

//in vec2 textureCoords;
in vec4 colors;
out vec4 fragColour;

//uniform sampler2D guiTexture;

void main(void) {
	fragColour = colors; //vec4(0, 1, 0, 1);//texture(guiTexture,textureCoords);
}