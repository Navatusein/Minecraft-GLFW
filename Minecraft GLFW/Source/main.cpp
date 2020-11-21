#pragma comment(linker, "/STACK:67108864")

#include <Windows.h>
#include <iostream>
#include <ctime>
#include <future>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "ErrorHandling.h"

#include "Window/Window.h"
#include "Window/Events.h"
#include "Window/Camera.h"

#include "Graphic/Shader.h"

#include "Graphic/GUI/GUIMesh.h"

#include "Mesh/Mesh.h"

#include "Mesh/BigMesh.h"
#include "Mesh/ShardMesh.h"

#include "World/World.h"
#include "World/ChunkUpdaterCall.h"

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
		return -1;
	}

	Shader* guiShader = CreateShaderProgram("Resource/Shader/guiShaderVertex.glsl", "Resource/Shader/guiShaderFragment.glsl");
	if (guiShader == nullptr) {
		std::cerr << "[main] Failed to load gui shader" << std::endl;
		Window::Terminate();
		return -1;
	}

	Texture* textureAtlas = CreateTexture("Resource/Textures/TextureAtlas.png");
	if (textureAtlas == nullptr) {
		std::cerr << "[main] Failed to load texture atlas" << std::endl;
		Window::Terminate();
		return -1;
	}

	Texture * guiTextureAtlas = CreateTexture("Resource/Textures/Untitled.png");
	if(guiTextureAtlas == nullptr) {
		std::cerr << "[main] Failed to load gui texture atlas" << std::endl;
		Window::Terminate();
		return -1;
	}


	glClearColor(0.24f, 0.47f, 0.69f, 1);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	float vertices[] = {
		-0.075f, -0.1f, 0.f, 0.f,
		0.075f, -0.1f, 1.f, 0.f,
		0.075f, 0.1f, 1.f, 1.f,
		-0.075f, 0.1f, 0.f, 1.f,
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};


	mat4 Model(1.f);
	Model = translate(Model, vec3(0.5f, 0, 0));

	Events::ToogleCursor();

	World world(textureAtlas, 1);

	GUIMesh gui(guiTextureAtlas);

	Player Steve(&world);

	gui.Push((Vertex4<float>*)vertices, 4, indices, 6);
	gui.UpdateMesh();


	std::future<void> fut = std::async(std::launch::async, &Call_UpdateChunks, std::ref(world), 3000); // launching asynchronous task to update all chunks once

	//Main loop
	while (!Window::WindowShouldClose()) {
		Steve.Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		shader->Bind();
		shader->UniformMatrix("projview", Steve.getCamera()->GetProjection() * Steve.getCamera()->GetView());
		shader->Unbind();

		//Draw here
		world.Draw(shader);
		gui.Draw(guiShader);
	
		

		// Swapping frame buffers
		Window::SwapBuffers();
		Events::PullEvents();
	}
	
	delete shader;
	delete guiShader; //fix memory leak 
	delete textureAtlas;
	

	// Closing the window
	Window::Terminate();
	return 0;
}
