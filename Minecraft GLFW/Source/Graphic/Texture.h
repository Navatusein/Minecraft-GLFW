#pragma once

#include <iostream>
#include <string>
#include <SOIL.h>
#include <GL/glew.h>

class Texture {
public:
	unsigned int id;
	int width;
	int height;
	Texture(unsigned int id, int width, int height);
	~Texture();

	void Bind();
	void Unbind();
};

Texture* CreateTexture(std::string File);
