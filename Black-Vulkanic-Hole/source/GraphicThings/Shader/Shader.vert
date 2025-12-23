#version 450

vec2 positions[3] = vec2[](
	vec2(0.0, -0.5),
	vec2(0.5, 0.5),
	vec2(-0.5, 0.5)
);

void main()
{
//gl_Position is a global variable that we use to "return" the position
	gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);//3rd is the z value, 4th is a normalizations value
}