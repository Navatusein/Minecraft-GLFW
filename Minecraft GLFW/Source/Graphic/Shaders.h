#pragma once
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shaders {
public:
	unsigned int id;

	Shaders(unsigned int id);
	~Shaders();

	void Use();
	void UniformMatrix(std::string name, glm::mat4 matrix);
};

Shaders* CreateShederProgram(std::string vertexFile, std::string fragmentFile);

