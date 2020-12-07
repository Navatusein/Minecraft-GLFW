#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Texture* guitexture, float windowscale) {
	gui = new GUIMesh(guitexture, windowscale);
	crosshair = new Crosshair(gui, 1);

	crosshair->Scale(0.08f, 0.08f);
	crosshair->SetMode(CrosshairMode::Standard);
	crosshair->Push();
	gui->UpdateMesh();

	gltInit();

	text = gltCreateText();
	gltSetText(text, "Hello World!");

}

PlayerGUI::~PlayerGUI() {
	delete gui;
	delete crosshair;

	// Deleting text
	gltDeleteText(text);
	// Destroy glText
	gltTerminate();
}

void PlayerGUI::Draw(Shader* program) {
	gui->Draw(program);

	//Begin text drawing (this for instance calls glUseProgram)
	gltBeginDraw();

	//Draw any amount of text between begin and end
	gltColor(1.0f, 1.0f, 1.0f, 1.0f);
	gltDrawText2D(text, 10, 30, 1.3);

	//Finish drawing text
	gltEndDraw();
}

void PlayerGUI::UpdateText(std::vector<std::string> TextArray) {

	std::string FinalText;

	for (unsigned short i = 0; i < TextArray.size(); i++) {
		FinalText += TextArray[i] + "\n";
	}

	gltSetText(text, FinalText.c_str());
}

void PlayerGUI::ToggleCrosshair() {
}

void PlayerGUI::TriggerCrosshair() {
}
