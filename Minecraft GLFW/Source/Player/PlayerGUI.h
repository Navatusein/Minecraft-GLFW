#pragma once
#include "../Graphic/GUI/GUIMesh.h"
#include "../Graphic/GUI/GUIElement.h"
#include "../Graphic/GUI/GUIElements/Crosshair.h"
#include "../Graphic/Texture.h"
#include "../Graphic/Shader.h"

class PlayerGUI
{
private:
	GUIMesh* gui;
	Crosshair* crosshair;
public:
	PlayerGUI(Texture* guitexture, float windowscale);
	~PlayerGUI();

	void Draw(Shader* program);

	void ToggleCrosshair();
	void TriggerCrosshair();
};

