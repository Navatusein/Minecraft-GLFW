#include <iostream>

#include "World.h"

World::World(Texture* textureAtl) {
	textureAtlas = textureAtl;
	xPos = 0;
	yPos = 0;
	zPos = 0;

	startChunk = new Chunk(textureAtl, xPos - DRAW_DISTANCE, yPos, zPos - DRAW_DISTANCE);

	Chunk* temp = startChunk;
	Chunk* tempx = startChunk;
	for(int x = xPos - DRAW_DISTANCE; x < xPos + DRAW_DISTANCE; x++) {
		tempx = startChunk;

		for(int z = zPos - DRAW_DISTANCE; z < zPos + DRAW_DISTANCE; z++) {

			startChunk->nZPos = new Chunk(textureAtl, x, yPos, z + 1);
			startChunk = startChunk->nZPos;
		}

		startChunk = tempx;
		startChunk->nXPos = new Chunk(textureAtl, x + 1, yPos, zPos);
		startChunk = startChunk->nXPos;
	}
	startChunk = temp;

}

World::~World() {
}

void World::LoadChunk() {
}

void World::UnloadChunk() {
}

void World::GenerateChunk() {
	

	startChunk->Fill();
	startChunk->Update();

	Chunk* temp = startChunk;
	Chunk* tempx = startChunk;
	for(int x = -DRAW_DISTANCE; x < DRAW_DISTANCE; x++) {
		tempx = startChunk;
	

		for(int z = -DRAW_DISTANCE; z < DRAW_DISTANCE; z++) {
			startChunk = startChunk->nZPos;
			
			startChunk->Fill();
			startChunk->Update();
		}
		
		startChunk = tempx;
		startChunk = startChunk->nXPos;
		startChunk->Fill();
		startChunk->Update();
	}
	startChunk = temp;
}

void World::Draw(Shader* program) {
	Chunk* temp = startChunk;
	Chunk* tempx = startChunk;

	for(int x = -DRAW_DISTANCE; x < DRAW_DISTANCE; x++) {
		tempx = startChunk;

		for(int z = -DRAW_DISTANCE; z < DRAW_DISTANCE; z++) {
			startChunk->Draw(program);
			startChunk = startChunk->nZPos;
		}
		startChunk = tempx;
		startChunk = startChunk->nXPos;
	}
	startChunk = temp;

}
