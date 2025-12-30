#version 450

//	 vvfrom location 0 (pos, address...)
//   vv         from vv cpu
//   vv               as vv 2 f32
//	 vv  	    	 vv  vv  name vv
layout(location = 0) in vec2 position;

void main()
{
//gl_Position is a global variable that we use to "return" the position
	gl_Position = vec4(position, 0.0, 1.0);//3rd is the z value, 4th is a normalizations value
}