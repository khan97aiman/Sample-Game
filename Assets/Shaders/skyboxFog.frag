#version 330 core

uniform sampler2D skyboxTex;

in Vertex {
	vec2 texCoord;
} IN;

out vec4 fragColour;
const float offset = 1.0 / 300.0;  

void main(void)	{
	//creating blur effect
	vec2 offsets[9] = vec2[] (
		vec2(-offset,  offset), // top-left
		vec2( 0.0f,    offset), // top-center
		vec2( offset,  offset), // top-right
		vec2(-offset,  0.0f),   // center-left
		vec2( 0.0f,    0.0f),   // center-center
		vec2( offset,  0.0f),   // center-right
		vec2(-offset, -offset), // bottom-left
		vec2( 0.0f,   -offset), // bottom-center
		vec2( offset, -offset)  // bottom-right    
	);

	float kernel[9] = float[] (
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16  
	);

	// float kernel[9] = float[] (
	// 	1.0, 1.0, 1.0,
	// 	1.0, -8, 1.0,
	// 	1.0, 1.0, 1.0  
	// );
	
	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++)
	{
		sampleTex[i] = texture(skyboxTex, IN.texCoord + offsets[i]).xyz;
	}
	vec3 col = vec3(0.0);
	for(int i = 0; i < 9; i++)
		col += sampleTex[i] * kernel[i];

	fragColour = vec4(col, 1.0);
}