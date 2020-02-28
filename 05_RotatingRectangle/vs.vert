#version 440 core

out vec3 vColor;

vec3 colors[] = {vec3(1.0f, 0.0f, 0.0f),
                 vec3(0.0f, 1.0f, 0.0f),
                 vec3(0.0f, 0.0f, 1.0f)};

vec3 positions[] = {vec3(-0.25f, -0.25f, 0.5f),
                    vec3( 0.25f, -0.25f, 0.5f),
                    vec3( 0.25f,  0.25f, 0.5f)};

void main()
{
    gl_Position = vec4(positions[gl_VertexID].xyz, 1.0f);
    vColor = colors[gl_VertexID % 3];
}

