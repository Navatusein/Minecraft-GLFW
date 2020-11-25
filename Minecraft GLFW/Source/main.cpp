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
#include "Graphic/GUI/GUIElement.h"

#include "Mesh/Mesh.h"

#include "Mesh/BigMesh.h"
#include "Mesh/ShardMesh.h"

#include "World/World.h"
#include "World/ChunkUpdaterCall.h"

#include "Player/Player.h"

#include "World/Voxel/VoxelDataBase.h"

//In one C or C++ file, define GLT_IMPLEMENTATION prior to inclusion to create the implementation.
#define GLT_IMPLEMENTATION
#include "FontRender/gltext.h"

using namespace glm;

int main() {

	srand(time(0));

	//Window initialization
	Window::Initialize("Hello world", false);
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

	Texture * guiTextureAtlas = CreateTexture("Resource/Textures/Reticle.png");
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

	GUIMesh gui(guiTextureAtlas, (float)Window::Width/(float)Window::Height);

	Player Steve(&world);

	GUIElement crosshair(&gui, 1);
	crosshair.Scale(0.08f, 0.08f);
	crosshair.Push();
	gui.UpdateMesh();

	std::future<void> fut = std::async(std::launch::async, &Call_UpdateChunks, std::ref(world), 3000); // launching asynchronous task to update all chunks once

	// Initialize glText
	gltInit();

	// Creating text
	GLTtext* text = gltCreateText();
	gltSetText(text, "Hello World!");

	//Main loop
	while (!Window::WindowShouldClose()) {

		Steve.Update();

		shader->Bind();
		shader->UniformMatrix("projview", Steve.getCamera()->GetProjection() * Steve.getCamera()->GetView());
		shader->Unbind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Draw here
		world.Draw(shader);
		gui.Draw(guiShader);
		
		// Begin text drawing (this for instance calls glUseProgram)
		gltBeginDraw();

		// Draw any amount of text between begin and end
		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
		gltDrawText2D(text, 10, 30, 1);

		// Finish drawing text
		gltEndDraw();

		// Pulling Events
		Events::PullEvents();

		// Swapping frame buffers
		Window::SwapBuffers();
	}
	
	delete shader;
	delete guiShader; //fix memory leak 
	delete textureAtlas;

	// Deleting text
	gltDeleteText(text);
	// Destroy glText
	gltTerminate();

	// Closing the window
	Window::Terminate();
	return 0;
}
