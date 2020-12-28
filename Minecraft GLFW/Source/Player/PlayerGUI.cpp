#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Texture* guitexture, float windowscale) {
	gui = new GUIMesh(guitexture, windowscale);
	crosshair = new Crosshair(gui, 1);

	crosshair->Scale(0.08f, 0.08f);
	crosshair->SetMode(CrosshairMode::Standard);
	crosshair->Push();
	gui->UpdateMesh();

	isF3menuOn = true;
	isStartupTextOn = true;

	gltInit();
	F3MenuText = gltCreateText();
	StartupText = gltCreateText();

	std::string PreferredMsg = 
		"\tControl buttons helper \n[W] [A] [S] [D] - Walking \n[Mouse Wheel] - Selecting a id of block for installation \n[F3] - Debug menu on / off \n[Space] - Jump \n[Ctrl] - Deceleration \n[Shift] - Boost \n[Tab] - Cursor on / off \n[ESC] - Close Game \n[X] - Close Control buttons helper \n[Left mouse button] - Break block \n[Right mouse button] - Place block";
	gltSetText(StartupText, PreferredMsg.c_str());
}

PlayerGUI::~PlayerGUI() {
	delete gui;
	delete crosshair;

	gltDeleteText(StartupText);
	gltDeleteText(F3MenuText);
	gltTerminate();
}

void PlayerGUI::Draw(Shader* program) {
	gui->Draw(program);
	
	gltBeginDraw();

	if (isStartupTextOn) {
		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
		gltDrawText2D(StartupText, 700, 230, 1.3);
	}

	if (isF3menuOn) {
		UpdateF3menuText();
		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
		gltDrawText2D(F3MenuText, 10, 30, 1.3);
	}
	
	gltEndDraw();
}

void PlayerGUI::SetF3MenuData(F3menu* Data) {
	F3Data = Data;
}

void PlayerGUI::UpdateF3menuText() {
	std::string F3Text = 
		"HandItemID: " + std::to_string(F3Data->ItemHandID) + 
		"\nFPS: " + std::to_string(F3Data->FPS) + 
		"\nPosition: x=" + std::to_string((int)F3Data->Position.x) + " y=" + std::to_string((int)F3Data->Position.y) + " z=" + std::to_string((int)F3Data->Position.z);
	gltSetText(F3MenuText, F3Text.c_str());

}

void PlayerGUI::ToggleF3menu() {
	if (F3Data) {
		isF3menuOn = !isF3menuOn;
	}
}

void PlayerGUI::ToogleStartupText() {
	isStartupTextOn = !isStartupTextOn;
}

void PlayerGUI::ToggleCrosshair() {
}

void PlayerGUI::TriggerCrosshair() {
}
