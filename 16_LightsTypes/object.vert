#version 440 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 aTextureCoord;

out vec3 Normal;
out vec3 FragmentPosition;
out vec2 TextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	// create transformation matrix
	mat4 transformation = projection * view * model;
	// all the matrices are row-order, so multiply by right side
	vec4 pos = vec4(aPos, 1);
	gl_Position = transformation * pos;
	// pass normals
	Normal = mat3(transpose(inverse(model))) * aNormal;
	// calculate fragment position in world space
	FragmentPosition = vec3(model * vec4(aPos, 1.0f));
	// pass texture coordinates
	TextureCoord = aTextureCoord;
}