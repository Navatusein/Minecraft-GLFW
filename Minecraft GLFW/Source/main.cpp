#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "ErrorHandling.h"

#include "Window/Window.h"
#include "Window/Events.h"
#include "Window/Camera.h"

#include "Graphic/Shader.h"
#include "Graphic/VoxelRenderer.h"
#include "Graphic/Texture.h"

#include "Mesh/Mesh.h"

#include "Voxel/Chunk.h"
#include "Voxel/Voxel.h"
#include "Voxel/Chunks.h"

float vertices[] = {
	// x    y
   -0.01f,-0.01f,
	0.01f, 0.01f,

   -0.01f, 0.01f,
	0.01f,-0.01f,
};

int attrs[] = {
		2,  0 //null terminator
};

using namespace glm;

int main() {
	//Window initialization
	Window::Initialize(1280, 800, "Hello world");
	Events::Initialize();

	Shader* shader = CreateShaderProgram("Resource/Shader/mainVertex.glsl", "Resource/Shader/mainFragment.glsl");
	if (shader == nullptr) {
		std::cout << "[main] Failed to load main shader" << std::endl;
		Window::Terminate();
		return 1;
	}

	Shader* crosshairShader = CreateShaderProgram("Resource/Shader/crosshairVertex.glsl", "Resource/Shader/crosshairFragment.glsl");
	if (crosshairShader == nullptr) {
		std::cerr << "[main] Failed to load crosshair shader" << std::endl;
		Window::Terminate();
		return 1;
	}

	Texture* texture = CreateTexture("Resource/Textures/block.png");
	if (texture == nullptr) {
		std::cout << "[main] Failed to load texture" << std::endl;
		delete shader;
		Window::Terminate();
		return 1;
	}

	CONSOLWRITE("Load");
	
	Chunks* chunks = new Chunks(8, 1, 8);
	Mesh** meshes = new Mesh * [chunks->volume];
	
	for (size_t i = 0; i < chunks->volume; i++)
		meshes[i] = nullptr;
	VoxelRenderer renderer(1024 * 1024 * 8);

	CONSOLWRITE("Chunks");

	glClearColor(0.6f, 0.62f, 0.65f, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Mesh* crosshair = new Mesh(vertices, 4, attrs);

	Camera* camera = new Camera(vec3(0, 0, 1), radians(70.0f));

	mat4 Model(1.f);
	Model = translate(Model, vec3(0.5f, 0, 0));

	float LastTime = glfwGetTime();
	float Delta = 0.0f;

	float CamX = 0.0f;
	float CamY = 0.0f;

	float Speed = 5;

	Events::ToogleCursor();




	CONSOLWRITE("Main Loop");
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

			camera->Rotation = mat4(1.f);
			camera->Rotate(CamY, CamX, 0);
		}
		{
			vec3 end;
			vec3 norm;
			vec3 iend;
			Voxel* vox = chunks->rayCast(camera->Position, camera->Front, 10.0f, end, norm, iend);
			if (vox != nullptr) {
				if (Events::JustClicked(KM_MOUSE_BUTTON_1)) {
					chunks->set((int)iend.x, (int)iend.y, (int)iend.z, 0);
				}
				if (Events::JustClicked(KM_MOUSE_BUTTON_2)) {
					chunks->set((int)(iend.x) + (int)(norm.x), (int)(iend.y) + (int)(norm.y), (int)(iend.z) + (int)(norm.z), 2);
				}
			}
		}

		Chunk* closes[27];
		for (size_t i = 0; i < chunks->volume; i++) {
			Chunk* chunk = chunks->chunks[i];
			if (!chunk->Modified)
				continue;
			chunk->Modified = false;
			if (meshes[i] != nullptr)
				delete meshes[i];

			for (int i = 0; i < 27; i++)
				closes[i] = nullptr;
			for (size_t j = 0; j < chunks->volume; j++) {
				Chunk* other = chunks->chunks[j];

				int ox = other->x - chunk->x;
				int oy = other->y - chunk->y;
				int oz = other->z - chunk->z;

				if (abs(ox) > 1 || abs(oy) > 1 || abs(oz) > 1)
					continue;

				ox += 1;
				oy += 1;
				oz += 1;
				closes[(oy * 3 + oz) * 3 + ox] = other;
			}
			Mesh* mesh = renderer.render(chunk, (const Chunk**)closes);
			meshes[i] = mesh;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader->Use();
		shader->UniformMatrix("projview", camera->GetProjection() * camera->GetView());
		texture->Bind();
		mat4 model(1.0f);
		for (size_t i = 0; i < chunks->volume; i++) {
			Chunk* chunk = chunks->chunks[i];
			Mesh* mesh = meshes[i];
			model = glm::translate(mat4(1.0f), vec3(chunk->x * ChunkW + 0.5f, chunk->y * ChunkH + 0.5f, chunk->z * ChunkD + 0.5f));
			shader->UniformMatrix("model", model);
			mesh->draw(GL_TRIANGLES);
		}

		crosshairShader->Use();
		crosshair->draw(GL_LINES);

		

		// Swapping frame buffers
		Window::SwapBuffers();
		Events::PullEvents();
	}

	delete shader;
	delete texture;
	delete chunks;
	delete crosshair;
	delete crosshairShader;


	// Closing the window
	Window::Terminate();
	return 0;
}
