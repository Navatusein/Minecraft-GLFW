//����������� ���������
#include<iostream>

//����������� ������ �������
#include"Window/Window.h"
#include"Events/Events.h"


int main() {
	//������������� ���� ����
	Window::Initialize(600, 600, "Hello world");

	//������� ���� ���������
	while (!Window::WindowShouldClose()) {

		//����� ������ �����������
		Window::SwapBuffers();
	}

	//�������� ���� ����
	Window::Terminate();
	return 0;
}