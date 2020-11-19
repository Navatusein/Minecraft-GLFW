#pragma once
#include <ctime>
#include "World.h" 

void Call_UpdateChunks(World& world, unsigned int timer) {
	clock_t alpha = clock();
	while(clock() - alpha < timer) {
	}
	world.UpdateChunks();
}