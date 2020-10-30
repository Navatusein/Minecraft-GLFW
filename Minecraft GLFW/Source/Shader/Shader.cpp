#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Shader.h"
#include "../ErrorHandling.h"

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
	GLCall(glDeleteProgram(mRendererID));
}

void Shader::Bind()
{
	GLCall(glUseProgram(mRendererID));
}

void Shader::Unbind()
{
	GLCall(glUseProgram(0));
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
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if(result == GL_FALSE)
	{
		int length = 0;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

		char* message = (char*)malloc(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "\n";
		std::cout << message << "\n";

		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(std::string& vertexShader, std::string& fragmentShader)
{
	unsigned int program;
	GLCall(program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDetachShader(program, vs));
	GLCall(glDetachShader(program, fs));

	return program;
}

void Shader::Uniform(std::string name)
{
	GLCall(int location = glGetUniformLocation(mRendererID, name.c_str()));
	if(location == -1)
	{
		std::cout << "warning: uniform is not initialized\nname: " << name << "\n";
	}
	else
	{
		GLCall(glUniform3f(location, 1.f, 0.f, 1.f));
	}
}


