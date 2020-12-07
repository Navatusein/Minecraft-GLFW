#pragma once

#include "Window.h"
#include "KeyMacros.h"

class Events {
private:

public:
	static bool* keys;
	static unsigned int* frames;
	static unsigned int current;
	static float x;
	static float y;
	static float deltaX;
	static float deltaY;
	static float deltaScrollY;
	static bool lockedCursor;
	static bool startedCursor;

	static int Initialize();
	static void PullEvents();

	static bool Pressed(int keycode);
	static bool JustPressed(int keycode);

	static bool Clicked(int button);
	static bool JustClicked(int button);

	static void ToogleCursor();
};

