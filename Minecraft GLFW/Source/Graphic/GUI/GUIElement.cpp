#include "GUIElement.h"

GUIElement::GUIElement(GUIMesh* parent) : parent(parent), scale(glm::vec2(1.f, 1.f)), position(0.f, 0.f), textureID(0){
}

GUIElement::GUIElement(GUIMesh* parent, unsigned short textureID) : parent(parent), scale(glm::vec2(1.f, 1.f)), position(0.f, 0.f), textureID(textureID) {
}

void GUIElement::Push() {
	float vertices[4*4];
	float u[2];
	float v[2];
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};
	{ // setting up vertex coordinates
		float verticesPos[] = {
	    -0.5f, -0.5f,
	    0.5f, -0.5f,
	    0.5f, 0.5f,
	    -0.5f, 0.5f,
		};
		for(int i = 0; i < 4; i++) {
			glm::vec2 temp = glm::vec2(verticesPos[i], verticesPos[i + 1]);
			temp *= scale;
			temp += position;
 			vertices[i * 4] = temp.x;
			vertices[i * 4 + 1] = temp.y;
		}
	}
	{ // setting up uv coordinates

	}
}




void GUIElement::SetTexture(unsigned short textureID) {
	this->textureID = textureID;
}

void GUIElement::Center() {
	position = glm::vec2(0.f, 0.f);
}

void GUIElement::Move(glm::vec2 val) {
	position += val;
}

void GUIElement::Move(float x, float y) {
	position += glm::vec2(x, y);
}

void GUIElement::Scale(glm::vec2 val) {
	scale *= val;
}

void GUIElement::Scale(float x, float y) {
	position *= glm::vec2(x, y);
}