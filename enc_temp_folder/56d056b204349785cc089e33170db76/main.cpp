#include <GL/glew.h>

#include <iostream>

#include "Window/Window.h"
#include "Window/Events.h"

#include "Vertex/VertexBuffer.h"
#include "Vertex/VertexArray.h"
#include "Vertex/IndexBuffer.h"

#include "Shader/ShaderTestr.h"

int main() {
	//Window initialization
	Window::Initialize(600, 600, "Hello world");
	Events::Initialize();


	/** FOLLOWING CODE NEEDS TO BE WRAPPED TO A CLASS **/

	GLfloat vertices[] = {
		// Позиции         // Цвета
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Нижний правый угол
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Нижний левый угол
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Верхний угол
	};

	float positions[8] = {
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 1
	};

	VertexArray VAO;
	VertexBuffer VBO(vertices, 2 * 4 * sizeof(float));

	VBLayout layout;
	layout.Push<float>(2);
	VAO.AddBuffer(VBO, layout);

	IndexBuffer IBO(indices, 6);


	Shader program("Resource/Shader/Vertex.glsl", "Resource/Shader/Fragment.glsl");

	/* freeing resources */
	VAO.Unbind();
	VBO.Unbind();
	IBO.Unbind();
	//program.Unbind();

	/** end **/

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

		VAO.Bind();
		VBO.Bind();
		program.Use();
		//program.Bind();

		//program.Uniform("uColor");

		/* for some reason shader is not working (triangles are white) */
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		//Swapping frame buffers
		Window::SwapBuffers();
	}

	//Closing the window
	Window::Terminate();
	return 0;
}