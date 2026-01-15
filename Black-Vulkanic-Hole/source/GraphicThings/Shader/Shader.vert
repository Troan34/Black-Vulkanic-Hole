#version 450

//	 vvfrom location 0 (pos, address...)
//   vv         from vv cpu
//   vv               as vv 3 f32
//	 vv  	    	 vv  vv  name vv
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform Push
{
	mat4 transform;
	vec3 color;
} push;


void main()
{
//gl_Position is a global variable that we use to "return" the position
	//gl_Position = vec4(push.transform * position + push.offset, 0.0, 1.0);//3rd is the z value, 4th is a normalizations value
	gl_Position = push.transform * vec4(position, 1.0);//4th value is omogeneuos coordinate
	fragColor = color;
}