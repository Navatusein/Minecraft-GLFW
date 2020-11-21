#pragma once

//GLEW in Satic Mode
#define GLEW_STATIC 

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
	static int Width;
	static int Height;

	static GLFWwindow* window;

	//Window initialization method
	static int Initialize(const char* title, bool fullscreen);
	
	//Window killing method
	static void Terminate();
	
	//Method for checking if a window is open
	static bool WindowShouldClose();
	
	//Window close method
	static void SetWindowShouldClose(bool flag);
	
	//Method for changing display buffers
	static void SwapBuffers();

	static void SetCursorMode(int mode);
};

