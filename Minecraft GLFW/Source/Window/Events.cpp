#include"Events.h"

#define SHIFT_MOUSE_BUTTON 1024

bool* Events::keys;
unsigned int* Events::frames;
unsigned int Events::current = 0;
float Events::x = 0;
float Events::y = 0;
float Events::deltaX = 0;
float Events::deltaY = 0;
bool Events::lockedCursor = false;
bool Events::startedCursor = false;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	if (Events::startedCursor) {
		Events::deltaX += xpos - Events::x;
		Events::deltaY += ypos - Events::y;
	}
	else {
		Events::startedCursor = true;
	}
	Events::x = xpos;
	Events::y = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) {
		Events::keys[SHIFT_MOUSE_BUTTON + button] = true;
		Events::frames[SHIFT_MOUSE_BUTTON + button] = Events::current;
	}
	else if (action == GLFW_RELEASE) {
		Events::keys[SHIFT_MOUSE_BUTTON + button] = false;
		Events::frames[SHIFT_MOUSE_BUTTON + button] = Events::current;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		Events::keys[key] = true;
		Events::frames[key] = Events::current;
	}
	else if (action == GLFW_RELEASE) {
		Events::keys[key] = false;
		Events::frames[key] = Events::current;
	}
}

void window_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	Window::Width = width;
	Window::Height = height;
}

int Events::Initialize() {
	GLFWwindow* window = Window::window;
	keys = new bool[1032];
	frames = new unsigned int[1032];

	memset(keys, false, 1032 * sizeof(bool));
	memset(frames, false, 1032 * sizeof(unsigned int));

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	return 0;
}

void Events::PullEvents() {
	current++;
	deltaX = 0.0f;
	deltaY = 0.0f;
	glfwPollEvents();
}

bool Events::Pressed(int keycode) {
	if (keycode < 0 || keycode >= SHIFT_MOUSE_BUTTON) {
		return false;
	}
	return keys[keycode];
}

bool Events::JustPressed(int keycode) {
	if (keycode < 0 || keycode >= SHIFT_MOUSE_BUTTON)
		return false;
	return keys[keycode] && frames[keycode] == current;
}

bool Events::Clicked(int button) {
	int index = SHIFT_MOUSE_BUTTON + button;
	return keys[index];
}

bool Events::JustClicked(int button) {
	int index = SHIFT_MOUSE_BUTTON + button;
	return keys[index] && frames[index] == current;
}

void Events::ToogleCursor() {
	lockedCursor = !lockedCursor;
	Window::SetCursorMode(lockedCursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}
