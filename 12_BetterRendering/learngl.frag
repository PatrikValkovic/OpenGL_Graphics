#version 440 core

in vec3 finalColor;
in vec2 wallTextureCoord;
in vec2 roofTextureCoord;

out vec4 color;

uniform sampler2D wallTexture;
uniform sampler2D roofTexture;

void main() {
    vec4 from_texture;

	if(wallTextureCoord.y < -4){ // its roof
		from_texture = texture(roofTexture, roofTextureCoord);
	}
	if(roofTextureCoord.y > 1) { // its wall
		from_texture = texture(wallTexture, wallTextureCoord);
	}


	color = mix(
		from_texture,
		vec4(finalColor, 1.0), 
		0.4);
}