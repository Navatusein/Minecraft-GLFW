#pragma once

//GLEW � ���������� ������
#define GLEW_STATIC 

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
	static GLFWwindow* window;

	//����� ������������� ����
	static int Initialize(int width, int height, const char* title);
	
	//����� �������� ����
	static void Terminate();
	
	//����� �������� ������� �� ����
	static bool WindowShouldClose();
	
	//����� �������� ����
	static void SetWindowShouldClose(bool flag);
	
	//����� ����� ������� �����������
	static void SwapBuffers();
};

