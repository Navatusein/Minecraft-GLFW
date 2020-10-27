#pragma once

//GLEW в сатическом режиме
#define GLEW_STATIC 

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
	static GLFWwindow* window;

	//Метод инициализации окна
	static int Initialize(int width, int height, const char* title);
	
	//Метод убийства окна
	static void Terminate();
	
	//Метод проверки открыто ли окно
	static bool WindowShouldClose();
	
	//Метод закрития окна
	static void SetWindowShouldClose(bool flag);
	
	//Метод смены буферов отображения
	static void SwapBuffers();
};

