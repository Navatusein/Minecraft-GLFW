#include "Window.h"

GLFWwindow* Window::window;
int Window::Width = 0;
int Window::Height = 0;

int Window::Initialize(int width, int height, GLFWmonitor* monitor, const char* title) {
	//Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Create a window
	window = glfwCreateWindow(width, height, title, monitor, nullptr);
	if (window == nullptr) {
		std::cout << "[Window] Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Initializing GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "[Window] Failed to initialize GLEW" << std::endl;
		return -1;
	}
	glViewport(0, 0, width, height);

	Window::Width = width;
	Window::Height = height;

	return 0;
}

void Window::Terminate() {
	glfwTerminate();
}

bool Window::WindowShouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::SetWindowShouldClose(bool flag) {
	glfwSetWindowShouldClose(window, flag);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(window);
}

void Window::SetCursorMode(int Mode) {
	glfwSetInputMode(window, GLFW_CURSOR, Mode);
}
