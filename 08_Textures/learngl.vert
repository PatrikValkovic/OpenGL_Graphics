#version 440 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 textureCoords;

out vec3 finalColor;
out vec2 texCoord;

uniform float rotation;

void main(){
	float rotRad = radians(rotation);
	mat3 matRotation = mat3(
		cos(rotRad), sin(rotRad), 0,
		-sin(rotRad), cos(rotRad), 0,
		0, 0, 1
	);
	gl_Position = vec4(matRotation * aPos, 1);
	finalColor = aColor;
	// rotate the texture as it is loaded into OpenGL upside down
	texCoord = vec2(textureCoords.x, 1 - textureCoords.y);
}