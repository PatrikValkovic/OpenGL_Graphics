#version 440 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aWallTexture;
layout (location=3) in vec2 aRoofTexture;

out vec3 finalColor;
out vec2 wallTextureCoord;
out vec2 roofTextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	// create transformation matrix
	mat4 transformation = projection * view * model;
	// all the matrices are row-order, so multiply by right side
	vec4 pos = vec4(aPos, 1);
	gl_Position = transformation * pos;

	finalColor = aColor;

	// rotate the textures as it is loaded into OpenGL upside down
	wallTextureCoord = vec2(aWallTexture.x, 1 - aWallTexture.y);
	roofTextureCoord = vec2(aRoofTexture.x, 1 - aRoofTexture.y);
}