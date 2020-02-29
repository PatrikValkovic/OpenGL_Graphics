#version 440 core

in vec3 finalColor;
in vec2 texCoord;

out vec4 color;

// first sampler automatically bind to GL_TEXTURE0
uniform sampler2D texSampler;
uniform sampler2D secSampler;

void main() {
	color = mix(texture(texSampler, texCoord), texture(secSampler, texCoord * 2), 0.4) * vec4(finalColor, 1.0);
}