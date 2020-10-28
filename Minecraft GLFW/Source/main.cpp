#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window/Window.h"
#include "Window/Events.h"

#include "Vertex/VertexBuffer.h"
#include "Vertex/VertexArray.h"

int main() {
	//Window initialization
	Window::Initialize(600, 600, "Hello world");
	Events::Initialize();

	//Main loop
	while (!Window::WindowShouldClose()) {
		Events::PullEvents();


		//Events test
		if (Events::JustPressed(P_KEY_ESCAPE)) {
			Window::SetWindowShouldClose(true);
		}
		if (Events::JustClicked(P_MOUSE_BUTTON_1)) {
			std::cout << "Work" << std::endl;
		}

		//Swapping frame buffers
		Window::SwapBuffers();
	}

	//Closing the window
	Window::Terminate();
	return 0;
}