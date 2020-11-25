#include "Mexception.h"

Mexception::Mexception(std::string message) : message(message) {}

std::string Mexception::getError() {
	return message;
}
