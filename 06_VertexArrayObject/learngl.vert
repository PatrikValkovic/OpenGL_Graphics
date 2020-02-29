#version 440 core

layout (location=0) in vec3 aPos;
layout (location=1) in float rot;

void main(){
	float rotRad = rot * 3.141592653 / 180.0;
	mat3 matRotation = mat3(
		cos(rotRad), sin(rotRad), 0,
		-sin(rotRad), cos(rotRad), 0,
		0, 0, 1
	);
	gl_Position = vec4(matRotation * aPos, 1);
}