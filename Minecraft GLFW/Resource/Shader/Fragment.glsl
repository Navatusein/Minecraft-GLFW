#version 330 core

in vec4 a_color;

layout(location = 0)out vec4 f_color;

void main()
{
	f_color = a_color;
};
