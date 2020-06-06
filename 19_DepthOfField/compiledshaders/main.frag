#version 440 core





//////////////////
//// CONTANTS ////
//////////////////









///////////////////////
//// END CONSTANTS ////
///////////////////////




in vec3 Normal;
in vec4 Color;
in vec3 Position;
in vec2 TextureCoords[4];

out vec4 color;

uniform sampler2D diffuse_texture;
uniform int diffuse_coord;

void main() {

	vec3 fragmentColor = vec3(Color);
	if(diffuse_coord >= 0){
		fragmentColor = vec3(texture(diffuse_texture, vec2(-1.0, -1.0) + TextureCoords[diffuse_coord]));
	}
	color = vec4(fragmentColor, 1);
	return;
}
