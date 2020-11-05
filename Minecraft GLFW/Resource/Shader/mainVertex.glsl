#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texCoord;

out vec4 a_color;
out vec2 a_texCoord;

uniform mat4 transform;
uniform mat4 projview;

void main(){
	a_color = vec4(1.0f,1.0f,1.0f,1.0f);
	a_texCoord = vec2(v_texCoord.x, 1.0-v_texCoord.y);
	gl_Position = projview* transform * vec4(v_position, 1.0);
}