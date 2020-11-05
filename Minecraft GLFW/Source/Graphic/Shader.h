#pragma once
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader {
public:
	unsigned int id;

	Shader(unsigned int id);
	~Shader();

	void Use();
	void UniformMatrix(std::string name, glm::mat4 matrix);
};

Shader* CreateShaderProgram(std::string vertexFile, std::string fragmentFile);

