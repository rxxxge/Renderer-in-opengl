#version 330 core
out vec4 FragColor;

in vec3 lightColor;

uniform vec3 color;

void main()
{
    FragColor = vec4(color, 1.0); // set all 4 vector values to 1.0
}