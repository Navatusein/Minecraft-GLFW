#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Texture* guitexture, float windowscale) {
	gui = new GUIMesh(guitexture, windowscale);
	crosshair = new Crosshair(gui, 1);

	crosshair->Scale(0.08f, 0.08f);
	crosshair->SetMode(CrosshairMode::Standard);
	crosshair->Push();
	gui->UpdateMesh();

	GLTtext* text = gltCreateText();
	gltSetText(text, "Hello World!");

}

PlayerGUI::~PlayerGUI() {
	delete gui;
	delete crosshair;
}

void PlayerGUI::Draw(Shader* program) {
	gui->Draw(program);
}

void PlayerGUI::ToggleCrosshair() {
}

void PlayerGUI::TriggerCrosshair() {
}
