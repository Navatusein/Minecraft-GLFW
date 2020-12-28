#pragma once

#include "../Graphic/GUI/GUIMesh.h"
#include "../Graphic/GUI/GUIElement.h"
#include "../Graphic/GUI/GUIElements/Crosshair.h"
#include "../Graphic/Texture.h"
#include "../Graphic/Shader.h"

#define GLT_IMPLEMENTATION
#include "../FontRender/gltext.h"

struct F3menu {
	unsigned short ItemHandID;
	unsigned short FPS;
	glm::vec3 Position;
};

class PlayerGUI
{
private:
	GUIMesh* gui;

	Crosshair* crosshair;

	GLTtext* F3MenuText;
	GLTtext* StartupText;

	F3menu* F3Data;

	bool isStartupTextOn;

	bool isF3menuOn;

	void UpdateF3menuText();
public:
	PlayerGUI(Texture* guitexture, float windowscale);
	~PlayerGUI();

	void Draw(Shader* program);

	void SetF3MenuData(F3menu* Data);

	void ToggleF3menu();
	void ToogleStartupText();

	void ToggleCrosshair(); // this doesn't seem to be used
	void TriggerCrosshair(); // this doesn't seem to be used
};

