#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window/Window.h"
#include "Window/Events.h"

#include"Graphic/Shaders.h"

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
		std::cerr << "failed to load shader" << std::endl;
		Window::Terminate();
		return 1;
	}

	// Create VAO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glClearColor(0.6f, 0.62f, 0.65f, 1);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Main loop
	while (!Window::WindowShouldClose()) {
		Events::PullEvents();

		//Events test
		if (Events::JustPressed(P_KEY_ESCAPE)) {
			Window::SetWindowShouldClose(true);
		}
		if (Events::JustClicked(P_MOUSE_BUTTON_1)) {
			glClearColor(0.8f, 0.4f, 0.2f, 1);
			std::cout << "Work" << std::endl;
		}
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw VAO
		shader->Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		//Swapping frame buffers
		Window::SwapBuffers();
	}

	delete shader;
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	//Closing the window
	Window::Terminate();
	return 0;
}