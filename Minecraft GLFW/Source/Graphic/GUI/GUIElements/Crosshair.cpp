#include "Crosshair.h"

Crosshair::Crosshair(GUIMesh* parent, unsigned short textureID) : GUIElement(parent, textureID) {
	mode = CrosshairMode::None;
}

void Crosshair::SetMode(CrosshairMode newMode) {
	mode = newMode;
}
