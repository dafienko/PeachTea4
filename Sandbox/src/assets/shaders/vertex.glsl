#version 330
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec4 vCol;

uniform mat4 MVP;

out vec4 color;

void main()
{
    gl_Position = MVP * vec4(vPos.xyz, 1.0);
    color = vCol;
}
