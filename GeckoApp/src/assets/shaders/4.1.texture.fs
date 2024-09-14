#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float mixValue;
uniform float mixFlag;
uniform vec3 color;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x, 1.0 - TexCoord.y)), mixValue);
	FragColor = mix(vec4(color, 1.0), texture(texture2, vec2(TexCoord.x, 1.0 - TexCoord.y)), mixFlag);
}