#version 330 core

layout(location = 0) in vec4 position;

out vec4 a_color;

void main()
{
	a_color = vec4(0.2f, 0.8f, 0.4f, 1.f);
	gl_Position = position;
};