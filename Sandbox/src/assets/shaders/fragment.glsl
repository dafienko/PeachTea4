#version 330

in vec4 color;

out vec4 FragColor;

void main()
{
    //FragColor = vec4(1, 0, 0, 1);
    FragColor = color;
}
