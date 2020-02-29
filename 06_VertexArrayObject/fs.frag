#version 440 core

in vec3 vColor;
out vec4 color;

void main()
{
  color = vec4(vColor.rgb, 1.0f);
}
