#pragma once

#include "../Graphic/GUI/GUIMesh.h"
#include "../Graphic/GUI/GUIElement.h"
#include "../Graphic/GUI/GUIElements/Crosshair.h"
#include "../Graphic/Texture.h"
#include "../Graphic/Shader.h"

#define GLT_IMPLEMENTATION
#include "../FontRender/gltext.h"

class PlayerGUI
{
private:
	GUIMesh* gui;
	Crosshair* crosshair;
	GLTtext* text;
public:
	PlayerGUI(Texture* guitexture, float windowscale);
	~PlayerGUI();

	void Draw(Shader* program);

	void UpdateText(std::vector<std::string> TextArray);

	void ToggleCrosshair();
	void TriggerCrosshair();
};

