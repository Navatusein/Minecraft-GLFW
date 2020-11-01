#pragma once

#include <iostream>
#include <string>
#include <SOIL.h>
#include <GL/glew.h>

class Textures {
public:
	unsigned int id;
	int width;
	int height;
	Textures(unsigned int id, int width, int height);
	~Textures();

	void Bind();
	void Unbind();
};

Textures* CreateTexture(std::string File);
