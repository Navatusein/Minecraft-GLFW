#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "ErrorHandling.h"

#include "Window/Window.h"
#include "Window/Events.h"
#include "Window/Camera.h"

#include"Graphic/Shaders.h"
#include"Graphic/Textures.h"

#include "Vertex/VertexArray.h"
#include "Vertex/VertexBuffer.h"

#define oldVAO false

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

	// Create VAO
#if oldVAO == 1

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
	
#else
	
	VertexBuffer VBO(vertices, 6);
	VertexArray VAO;

	VAO.AddBuffer(VBO);

	VAO.Unbind();
	VBO.Unbind();

#endif

	glClearColor(0.6f, 0.62f, 0.65f, 1);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Camera* camera = new Camera(vec3(0, 0, 1), radians(70.0f));

	mat4 Model(1.0f);
	Model = translate(Model, vec3(0.5f, 0, 0));

	float LastTime = glfwGetTime();
	float Delta = 0.0f;

	float CamX = 0.0f;
	float CamY = 0.0f;

	float Speed = 5;

	Events::ToogleCursor();

	//Main loop
	while (!Window::WindowShouldClose()) {

		float currentTime = glfwGetTime();
		Delta = currentTime - LastTime;
		LastTime = currentTime;

		// Events test
		if (Events::JustPressed(KM_KEY_ESCAPE)) {
			Window::SetWindowShouldClose(true);
		}
		if (Events::JustPressed(KM_KEY_TAB)) {
			Events::ToogleCursor();
		}

		if (Events::JustClicked(KM_MOUSE_BUTTON_1)) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		}
		if (Events::JustClicked(KM_MOUSE_BUTTON_2)) {
			glClearColor(0.6f, 0.62f, 0.65f, 1.0f);
		}

		if (Events::Pressed(KM_KEY_W)) {
			camera->Position += camera->Front * Delta * Speed;
		}
		if (Events::Pressed(KM_KEY_S)) {
			camera->Position -= camera->Front * Delta * Speed;
		}
		if (Events::Pressed(KM_KEY_D)) {
			camera->Position += camera->Right * Delta * Speed;
		}
		if (Events::Pressed(KM_KEY_A)) {
			camera->Position -= camera->Right * Delta * Speed;
		}
		if (Events::Pressed(KM_KEY_SPACE)) {
			camera->Position += camera->Up * Delta * Speed;
		}
		if (Events::Pressed(KM_KEY_LEFT_SHIFT)) {
			camera->Position -= camera->Up * Delta * Speed;
		}

		if (Events::lockedCursor) {
			CamY += -Events::deltaY / Window::Height * 2;
			CamX += -Events::deltaX / Window::Height * 2;

			if (CamY < -radians(89.0f)) {
				CamY = -radians(89.0f);
			}
			if (CamY > radians(89.0f)) {
				CamY = radians(89.0f);
			}

			camera->Rotation = mat4(1.0f);
			camera->Rotate(CamY, CamX, 0);
		}

		glClear(GL_COLOR_BUFFER_BIT);


		// Draw VAO
		shader->Use();
		shader->UniformMatrix("model", Model);
		GLCall(shader->UniformMatrix("projview", camera->GetProjection() * camera->GetView()));
		texture->Bind();

#if oldVAO == 1

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		
#else
		VAO.Bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		VAO.Unbind();
#endif

		// Swapping frame buffers
		Window::SwapBuffers();
		Events::PullEvents();
	}

	delete shader;
	delete texture;

#if oldVAO == 1	
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
#endif

	// Closing the window
	Window::Terminate();
	return 0;
}
