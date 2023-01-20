#version 330 core

uniform samplerCube cubeTex;
uniform bool useFog = false;
uniform vec4 fogColour;

in Vertex {
	vec3 viewDir;
} IN;

out vec4 fragColour;
const float belowHorizonLevel = 0.0f;
const float aboveHorizonLevel = 0.5f;

void main(void)	{
	vec4 samp = texture(cubeTex, normalize(IN.viewDir));
	fragColour = pow(samp, vec4(2.2f));

	if (useFog) {
		float ratio = clamp((IN.viewDir.y - belowHorizonLevel) / (aboveHorizonLevel - belowHorizonLevel), 0.0, 1.0);
		fragColour = mix(fogColour, fragColour, ratio);
	}
}