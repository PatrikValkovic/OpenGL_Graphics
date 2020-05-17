#version 440 core

layout (location=0) in vec3 aPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(){

	mat4 transformation = projection * view; // * model;

	vec4 pos = vec4(aPosition, 1);
	gl_Position = transformation * pos;
}