#pragma once

#include "../GUIElement.h"

enum class CrosshairMode
{
	None,
	Pickaxe,
	Axe,
	Melee,
	Ranged,
	Magic,
};

class Crosshair : public GUIElement
{
private:
	CrosshairMode mode;
public:
	Crosshair(GUIMesh* parent, unsigned short textureID);

	void SetMode(CrosshairMode newMode);
};

