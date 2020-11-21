#pragma once
#include <glm/ext.hpp>

#include "GUIMesh.h"

class GUIElement
{
private:
	unsigned short textureID;
	glm::vec2 position;
	glm::vec2 scale;

	GUIMesh* parent;
public:
	GUIElement(GUIMesh* parent);
	GUIElement(GUIMesh* parent, unsigned short textureID);

	void Push();

	void SetTexture(unsigned short textureID);

	void Center();

	void Move(glm::vec2 val);
	void Move(float x, float y);

	void Scale(glm::vec2 val);
	void Scale(float x, float y);
};

