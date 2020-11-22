#include "GUIElement.h"

GUIElement::GUIElement(GUIMesh* parent) : parent(parent), scale(glm::vec2(1.f, 1.f)), position(0.f, 0.f), textureID(0){
	scale.x /= parent->GetMonitorScale();
}

GUIElement::GUIElement(GUIMesh* parent, unsigned short textureID) : parent(parent), scale(glm::vec2(1.f, 1.f)), position(0.f, 0.f), textureID(textureID) {
	scale.x /= parent->GetMonitorScale();
}

void GUIElement::Push() {
	float vertices[4*4];
	float u[4];
	float v[4];
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};
	{ // setting up vertex coordinates
		// this code is retarded

		float verticesPos[] = {
	    -0.5f, -0.5f,
	    0.5f, -0.5f,
	    0.5f, 0.5f,
	    -0.5f, 0.5f,
		};
		int counter = 0;
		for(int i = 0; i < 4; i++) {
			glm::vec2 temp = glm::vec2(verticesPos[i*2], verticesPos[i*2 + 1]);
			temp *= scale;
			temp += position;
			std::cout << temp.x << " " << temp.y << "\n";
 			vertices[counter] = temp.x;
			vertices[counter + 1] = temp.y;
			counter += 4;
		}

	}
	// setting up uv coordinates
	switch(textureID) {
		// this is fucking retarded too
		case 1:
			vertices[2] = 0;    vertices[3] = 0;
			vertices[6] = 1;    vertices[7] = 0;
			vertices[10] = 1;  vertices[11] = 1;
			vertices[14] = 0;  vertices[15] = 1;
	}
	parent->Push((Vertex4<float>*)vertices, 4, indices, 6);
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
	scale *= glm::vec2(x, y);
}