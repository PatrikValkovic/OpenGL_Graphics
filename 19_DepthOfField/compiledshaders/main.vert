#version 440 core





//////////////////
//// CONTANTS ////
//////////////////









///////////////////////
//// END CONSTANTS ////
///////////////////////




layout (location=0) in vec3 aPosition;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec4 aColor;
layout (location=3) in vec2 aTextureCoords[4];

out vec3 Normal;
out vec4 Color;
out vec3 Position;
out vec2 TextureCoords[4];

uniform mat4 modelintern;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(){

	mat4 transformation = projection * view * model;


	Normal = aNormal;
	Color = aColor;
	Position = vec3(model * vec4(aPosition, 1.0f));
	for(uint i=0;i < 4;i++)
		TextureCoords[i]=aTextureCoords[i];

	gl_Position = transformation * vec4(aPosition, 1);
}
