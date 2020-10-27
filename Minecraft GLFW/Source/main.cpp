//Подключение библиотек
#include<iostream>

//Подключение файлов проекта
#include"Window/Window.h"
#include"Window/Events.h"


int main() {
	//Инициализация окна игры
	Window::Initialize(600, 600, "Hello world");
	Events::Initialize();

	//Главный цикл программы
	while (!Window::WindowShouldClose()) {
		Events::PullEvents();

		//Смена буфера отображения
		Window::SwapBuffers();
	}

	//Убийство окна игры
	Window::Terminate();
	return 0;
}