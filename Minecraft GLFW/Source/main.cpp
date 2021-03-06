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

#include "Player/PlayerGUI.h"

#include "World/Voxel/VoxelDataBase.h"

using namespace glm;

/*
**********************************************************
*To compile the project, set the Release and x64 settings*
**********************************************************
*/

int main() {

	srand(time(0));
	std::ios_base::sync_with_stdio(0);

	//Window initialization
	Window::Initialize("Hello world", false);
	Events::Initialize();

	//Initializatioo of main Shader
	Shader* shader = CreateShaderProgram("Resource/Shader/mainVertex.glsl", "Resource/Shader/mainFragment.glsl");
	if (shader == nullptr) {
		std::cerr << "[main] Failed to load main shader" << std::endl;
		Window::Terminate();
		return -1;
	}

	//Initializatioo of gui Shader
	Shader* guiShader = CreateShaderProgram("Resource/Shader/guiShaderVertex.glsl", "Resource/Shader/guiShaderFragment.glsl");
	if (guiShader == nullptr) {
		std::cerr << "[main] Failed to load gui shader" << std::endl;
		Window::Terminate();
		return -1;
	}

	//Initializatioo of texture atlas
	Texture* textureAtlas = CreateTexture("Resource/Textures/TextureAtlas.png");
	if (textureAtlas == nullptr) {
		std::cerr << "[main] Failed to load texture atlas" << std::endl;
		Window::Terminate();
		return -1;
	}

	//Initializatioo of gui atlas
	Texture * guiTextureAtlas = CreateTexture("Resource/Textures/Crosshair.png");
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

	mat4 Model(1.f);
	Model = translate(Model, vec3(0.5f, 0, 0));

	Events::ToogleCursor();

	World world(textureAtlas, 1);

	PlayerGUI pGUI(guiTextureAtlas, (float)Window::Width / (float)Window::Height);

	Player Steve(&world, &pGUI);
	

	// launching asynchronous task to update all chunks once after 3000ms
	auto fut = std::async(std::launch::async, &Call_UpdateChunks, std::ref(world), 3000); 
	
	//Main loop
	while (!Window::WindowShouldClose()) {

		Steve.Update();

		shader->Bind();
		shader->UniformMatrix("projview", Steve.getCamera()->GetProjection() * Steve.getCamera()->GetView());
		shader->Unbind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Draw here
		world.Draw(shader);
		Steve.DrawGUI(guiShader);

		Events::PullEvents();
		Window::SwapBuffers();
	}
	
	

	delete shader;
	delete guiShader;
	delete textureAtlas;

	Window::Terminate();

	return 0;
}
