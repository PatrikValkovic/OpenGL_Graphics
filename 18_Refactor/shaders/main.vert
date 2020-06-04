#version 440 core
#include "Constants.h"

layout (location=0) in vec3 aPosition;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec4 aColor;
layout (location=3) in vec2 aTextureCoords[MAX_TEXTURES];

out vec3 Normal;
out vec4 Color;
out vec3 Position;
out vec2 TextureCoords[MAX_TEXTURES];

uniform mat4 modelintern;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 clip_plane;

void main(){

	mat4 transformation = projection * view * model;


	Normal = mat3(transpose(inverse(model))) * aNormal;
	Color = aColor;
	Position = vec3(model * vec4(aPosition, 1.0f));
	for(uint i=0;i < MAX_TEXTURES;i++)
		TextureCoords[i]=aTextureCoords[i];

	gl_Position = transformation * vec4(aPosition, 1);
	vec4 in_view = view * model * vec4(aPosition, 1.0f);
	gl_ClipDistance[0] = -dot(clip_plane, in_view);
}
