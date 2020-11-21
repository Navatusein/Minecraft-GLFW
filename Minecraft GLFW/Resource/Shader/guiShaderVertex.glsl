#version 330 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_texCoord;

out vec2 a_texCoord;
out vec4 a_color;

void main(){
	a_texCoord = vec2(v_texCoord.x, 1.f - v_texCoord.y);
	gl_Position = vec4(v_position, 0.f, 1.f);
	a_color = vec4(1.f, 1.f, 1.f, 1.f);
}