#include <ctime>
#include <Windows.h>

#include "Crosshair.h"

Crosshair::Crosshair(GUIMesh* parent, unsigned short textureID) : GUIElement(parent, textureID) {
	mode = CrosshairMode::None;
}

void Crosshair::SetMode(CrosshairMode newMode) {
	mode = newMode;
}

void Crosshair::Toggle() {
	mode = CrosshairMode::None;
}

void Crosshair::Trigger() {
	mode = CrosshairMode::Triggered;
	SetTexture(2);
	fut = std::async(std::launch::async, &Crosshair::Untrigger, this, 50);
}

void Crosshair::Untrigger(int time) {
	clock_t alpha = clock();
	while(clock() - alpha < time) {
		Sleep(time);
	}
	if(mode == CrosshairMode::Triggered) {
		mode = CrosshairMode::Standard;
		SetTexture(1);
	}
}
