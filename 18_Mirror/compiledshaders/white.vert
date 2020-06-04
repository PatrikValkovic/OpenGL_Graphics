#version 440 core


layout (location=0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(){
	// create transformation matrix
	mat4 transformation = projection * view * model;
	// all the matrices are row-order, so multiply by right side
	vec4 pos = vec4(aPos, 1);
	gl_Position = transformation * pos;
}
