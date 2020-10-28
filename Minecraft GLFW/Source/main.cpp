#include <iostream>

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

		//Swapping frame buffers
		Window::SwapBuffers();
	}

	//Closing the window
	Window::Terminate();
	return 0;
}