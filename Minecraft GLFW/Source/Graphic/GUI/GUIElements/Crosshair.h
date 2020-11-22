#pragma once

#include <future>

#include "../GUIElement.h"

enum class CrosshairMode
{
	None,
	Standard,
	Triggered,
};

class Crosshair : public GUIElement
{
private:
	CrosshairMode mode;
	std::future<void> fut;
public:
	Crosshair(GUIMesh* parent, unsigned short textureID);

	void SetMode(CrosshairMode newMode);
	void Toggle();
	void Trigger();

private:
	void Untrigger(int time);
};

