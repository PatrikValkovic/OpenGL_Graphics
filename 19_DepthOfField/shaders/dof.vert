#version 440 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aTextureCoord;

out vec2 TextureCoords;

void main(){
	gl_Position = vec4(aPos, 1.0);
	TextureCoords = aTextureCoord;
}