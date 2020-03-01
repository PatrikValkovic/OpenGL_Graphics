#version 440 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 textureCoords;

out vec3 finalColor;
out vec2 texCoord;

uniform float rotation;

mat4 moveRect = mat4(
	1, 0, 0, 0.25,
	0, 1, 0, -0.25,
	0, 0, 1, 0,
	0, 0, 0, 1
);

mat4 moveRectBack = mat4(
	1, 0, 0, -0.25,
	0, 1, 0, 0.25,
	0, 0, 1, 0,
	0, 0, 0, 1
);

mat4 moveFarther = mat4(
	1, 0, 0, -0.2,
	0, 1, 0, 0.2,
	0, 0, 1, 0,
	0, 0, 0, 1
);

void main(){
	float rotRad = radians(rotation);

	mat4 rotRect = mat4(
		cos(4*rotRad), -sin(4*rotRad), 0, 0,
		sin(4*rotRad), cos(4*rotRad), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	mat4 rotAroundCenter = mat4(
		cos(rotRad), -sin(rotRad), 0, 0,
		sin(rotRad), cos(rotRad), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	mat4 scale = mat4(
		sin(2*rotRad), 0, 0, 0,
		0, sin(2 * rotRad), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	// all the matrices are row-order, so multiply by right side
	vec4 pos = vec4(aPos, 1);
	gl_Position = pos * moveRect * rotRect * scale * moveRectBack * moveFarther * rotAroundCenter;
	//gl_Position = pos * moveRect * rotRect;

	finalColor = aColor;
	// rotate the texture as it is loaded into OpenGL upside down
	texCoord = vec2(textureCoords.x, 1 - textureCoords.y);
}