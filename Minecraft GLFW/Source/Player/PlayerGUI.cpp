#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Texture* guitexture, float windowscale) {
	gui = new GUIMesh(guitexture, windowscale);
	crosshair = new GUIElement(gui, 1);

	crosshair->Scale(0.08f, 0.08f);
	crosshair->Push();
	gui->UpdateMesh();
}

PlayerGUI::~PlayerGUI() {
	delete gui;
	delete crosshair;
}

void PlayerGUI::Draw(Shader* program) {
	gui->Draw(program);
}
