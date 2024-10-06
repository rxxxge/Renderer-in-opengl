#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec3 a_Color;

out vec3 ourColor;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model * vec4(a_Pos, 1.0));
	gl_Position = projection * view * vec4(FragPos, 1.0);
	Normal = a_Normal;
	ourColor = a_Color;
}