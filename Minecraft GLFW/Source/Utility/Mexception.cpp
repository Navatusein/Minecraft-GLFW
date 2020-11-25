#include "Mexception.h"

Mexception::Mexception(std::string message) : message(message) {}

std::string Mexception::getError() {
	return message;
}

void Mexception::PrintError() {
	std::cerr << message << std::endl;
}
