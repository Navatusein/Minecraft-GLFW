#pragma once
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shaders {
public:
	unsigned int id;

	Shaders(unsigned int id);
	~Shaders();

	void Use();
};

Shaders* CreateShederProgram(std::string vertexFile, std::string fragmentFile);

