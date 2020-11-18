#pragma comment(linker, "/STACK:67108864")

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <Windows.h>

#include "ErrorHandling.h"

#include "Window/Window.h"
#include "Window/Events.h"
#include "Window/Camera.h"

#include"Graphic/Shader.h"

#include "Mesh/Mesh.h"

#include "Mesh/BigMesh.h"
#include "Mesh/ShardMesh.h"

#include "World/World.h"

#include "Player/Player.h"

using namespace glm;

int main() {

	srand(time(0));

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	int m_width = 2540, m_height = 1400;
	int xpos, ypos;
	//glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &m_width, &m_height);


	//Window initialization
	Window::Initialize(m_width, m_height, monitor, "Hello world");
	Events::Initialize();

	Shader* shader = CreateShaderProgram("Resource/Shader/mainVertex.glsl", "Resource/Shader/mainFragment.glsl");
	if (shader == nullptr) {
		std::cerr << "[main] Failed to load main shader" << std::endl;
		Window::Terminate();
		return 1;
	}
	/*
	Shader* crosshairShader = CreateShaderProgram("Resource/Shader/crosshairVertex.glsl", "Resource/Shader/crosshairFragment.glsl");
	if (shader == nullptr) {
		std::cerr << "[main] Failed to load crosshair shader" << std::endl;
		Window::Terminate();
		return 1;
	}
	*/

	Texture* textureAtlas = CreateTexture("Resource/Textures/TextureAtlas.png");
	if (textureAtlas == nullptr) {
		std::cerr << "[main] Failed to load texture" << std::endl;
		delete shader;
		Window::Terminate();
		return 1;
	}

	glClearColor(0.6f, 0.62f, 0.65f, 1);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mat4 Model(1.f);
	Model = translate(Model, vec3(0.5f, 0, 0));

	Events::ToogleCursor();

	World world(textureAtlas, 1);

	Player Steve(&world);

	//Main loop
	while (!Window::WindowShouldClose()) {

		Steve.KeyBoardUpdate();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		shader->Bind();
		shader->UniformMatrix("projview", Steve.getCamera()->GetProjection() * Steve.getCamera()->GetView());
		shader->Unbind();

		//Draw here
		world.Draw(shader);

		// Swapping frame buffers
		Window::SwapBuffers();
		Events::PullEvents();
	}
	
	delete shader;
	delete textureAtlas;

	// Closing the window
	Window::Terminate();
	return 0;
}
