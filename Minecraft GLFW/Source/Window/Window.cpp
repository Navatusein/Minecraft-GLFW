#include "Window.h"

GLFWwindow* Window::window;
int Window::Width = 0;
int Window::Height = 0;

int Window::Initialize(const char* title, bool fullscreen) {
	//Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if(monitor == nullptr) {
		std::cout << "[Window] Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		__debugbreak;
	}
	int m_width = 800, m_height = 600;
	int xpos = 0, ypos = 0;
	glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &m_width, &m_height);

	//Create a window
	if(fullscreen) {
		window = glfwCreateWindow(m_width, m_height, title, monitor, nullptr);
	}
	else {
		window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
	}
	if (window == nullptr) {
		std::cout << "[Window] Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		__debugbreak;
	}
	glfwMakeContextCurrent(window);

	//Initializing GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "[Window] Failed to initialize GLEW" << std::endl;
		__debugbreak;
	}
	glViewport(0, 0, m_width, m_height);

	Window::Width = m_width;
	Window::Height = m_height;

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
