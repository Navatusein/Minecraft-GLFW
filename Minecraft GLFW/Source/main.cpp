#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Window/Window.h"
#include "Window/Events.h"

#include"Graphic/Shaders.h"
#include"Graphic/Textures.h"


using namespace glm;

float vertices[] = {
	// x    y     z     u     v
   -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
	1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

	1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int main() {
	//Window initialization
	Window::Initialize(1280, 800, "Hello world");
	Events::Initialize();

	Shaders* shader = CreateShederProgram("Resource/Shader/main.glslv", "Resource/Shader/main.glslf");
	if (shader == nullptr) {
		std::cout << "[main] Failed to load shader" << std::endl;
		Window::Terminate();
		return 1;
	}

	Textures* texture = CreateTexture("Resource/Textures/1.png");
	if (texture == nullptr) {
		std::cout << "[main] Failed to load texture" << std::endl;
		delete shader;
		Window::Terminate();
		return 1;
	}

	mat4 model(1.0f);
	// Create VAO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glClearColor(0.6f, 0.62f, 0.65f, 1.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Main loop
	while (!Window::WindowShouldClose()) {
		Events::PullEvents();

		// Events test
		if (Events::JustPressed(P_KEY_ESCAPE)) {
			Window::SetWindowShouldClose(true);
		}
		if (Events::JustClicked(P_MOUSE_BUTTON_1)) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		}
		if (Events::JustClicked(P_MOUSE_BUTTON_2)) {
			glClearColor(0.6f, 0.62f, 0.65f, 1.0f);
		}
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw VAO
		shader->Use();
		texture->Bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// Swapping frame buffers
		Window::SwapBuffers();
	}

	delete shader;
	delete texture;
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	// Closing the window
	Window::Terminate();
	return 0;
}