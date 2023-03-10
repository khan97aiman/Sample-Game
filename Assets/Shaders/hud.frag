#version 400 core

in vec2 textureCoords;
out vec4 fragColour;

uniform sampler2D guiTexture;

void main(void) {
	fragColour = texture(guiTexture, textureCoords);
}