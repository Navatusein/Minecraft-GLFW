#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Shader.h"

struct source
{
	std::string VertexShader;
	std::string FragmentShader;
};

Shader::Shader(const std::string& vsPath, const std::string& fsPath) : mRendererID(0)
{
	source src;
	src.VertexShader = ParseShader(vsPath);
	src.FragmentShader = ParseShader(fsPath);
	mRendererID = CreateShader(src.VertexShader, src.FragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(mRendererID);
}

void Shader::Bind() const
{
	glUseProgram(mRendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

/*  Reads shader from .glsl file */
std::string Shader::ParseShader(const std::string& filePath)
{
	std::ifstream inStream(filePath);

	std::string line;
	std::stringstream ss;

	while(getline(inStream, line))
	{
		ss << line << "\n";
	}

	return ss.str();
}

bool Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "\n";
		std::cout << message << "\n";

		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(std::string& vertexShader, std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


