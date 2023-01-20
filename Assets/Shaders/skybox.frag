#version 330 core

uniform samplerCube cubeTexDay;
uniform samplerCube cubeTexNight;

uniform bool useFog = false;
uniform vec4 fogColour;

in Vertex {
	vec3 viewDir;
} IN;

out vec4 fragColour;
const float belowHorizonLevel = 0.0f;
const float aboveHorizonLevel = 0.25f;

void main(void)	{
	vec3 viewDir = normalize(IN.viewDir);
	vec4 dayTexture = texture(cubeTexDay, viewDir);
	vec4 nightTexture = texture(cubeTexNight, viewDir);
	vec4 finalTexture = mix(dayTexture, nightTexture, 1);

	fragColour = pow(finalTexture, vec4(2.2f));

	if (false) {
		float ratio = clamp((viewDir.y - belowHorizonLevel) / (aboveHorizonLevel - belowHorizonLevel), 0.0, 1.0);
		fragColour = mix(fogColour, fragColour, ratio);
	}
}