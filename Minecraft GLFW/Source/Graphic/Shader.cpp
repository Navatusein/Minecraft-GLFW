#include "Shader.h"

Shader::Shader(unsigned int id) : id(id) {}

Shader::~Shader() {
	glDeleteProgram(id);
}

void Shader::UniformMatrix(std::string name, glm::mat4 matrix) {
	GLuint TransformLoc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(TransformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::Bind() {
	glUseProgram(id);
}

void Shader::Unbind() {
	glUseProgram(0);
}

Shader* CreateShaderProgram(std::string vertexFile, std::string fragmentFile) {
	// Reading Files
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try {
		vShaderFile.open(vertexFile);
		fShaderFile.open(fragmentFile);
		std::stringstream vShadertream, fShadertream;

		vShadertream << vShaderFile.rdbuf();
		fShadertream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShadertream.str();
		fragmentCode = fShadertream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "[Shader] File not succesfully read" << std::endl;
		return nullptr;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "[Shader] VERTEX: compilation failed" << std::endl;
		std::cout << infoLog << std::endl;
		return nullptr;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "[Shader] FRAGMENT: compilation failed" << std::endl;
		std::cout << infoLog << std::endl;
		return nullptr;
	}

	// Shader Program
	GLuint id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		std::cout << "[Shader] PROGRAM: linking failed" << std::endl;
		std::cout << infoLog << std::endl;

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return nullptr;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return new Shader(id);
}
