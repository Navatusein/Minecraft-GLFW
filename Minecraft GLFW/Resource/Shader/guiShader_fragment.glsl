#version 330 core

in vec2 a_texCoord;
in vec4 a_color; 

out vec4 f_color;

uniform sampler2D u_texture0;

void main(){
	f_color = a_color * texture(u_texture0, a_texCoord);
}