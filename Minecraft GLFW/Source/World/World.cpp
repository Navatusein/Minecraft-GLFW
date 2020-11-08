#include <iostream>

#include "World.h"

World::World(Texture* textureAtl) : textureAtlas(textureAtl) {

	// it should be player chunk position
	xPos = 0;
	yPos = 0; 
	zPos = 0;

	Chunk* tempChunk = nullptr;
	Chunk* nextChunk;

	Chunk* temp;

	//to assign startChunk correctly
	bool firstIteration = 1;

	// list loops
	for(int x = -DRAW_DISTANCE; x < DRAW_DISTANCE; x++) {

		nextChunk = new Chunk(textureAtl, xPos + x, yPos, zPos - DRAW_DISTANCE);
		

		temp = nextChunk;
		if(firstIteration) {
			startChunk = nextChunk;
			firstIteration = 0;
		}

		for(int z = -DRAW_DISTANCE; z < DRAW_DISTANCE; z++) {			

			nextChunk->nZPos = new Chunk(textureAtl, xPos + x, yPos, zPos + z + 1);
			nextChunk->nZPos->nZNeg = nextChunk;
			

			// delete it later
			if(x == xPos && z == zPos) {
				playerChunk = nextChunk;
			}

			//nextChunk->nZNeg = tempChunk;
			if(tempChunk) {
				tempChunk->nXPos = nextChunk;
				tempChunk->nXPos->nXNeg = tempChunk;
				tempChunk = tempChunk->nZPos;
			}
			

			nextChunk = nextChunk->nZPos;
						
		}
		
		tempChunk = temp;
	}

}

World::~World() {
}

void World::LoadChunk() {
}

void World::UnloadChunk() {
}

void World::GenerateChunk() {
	Chunk* tempx = startChunk;


	Chunk* temp = startChunk;
	for(int x = -DRAW_DISTANCE; x < DRAW_DISTANCE; x++) {
		temp = startChunk;
	

		for(int z = -DRAW_DISTANCE; z < DRAW_DISTANCE; z++) {

			startChunk->Fill();
			startChunk->Update();

			startChunk = startChunk->nXPos;
		}
		
		startChunk = temp;
		startChunk = startChunk->nZPos;
	}

	startChunk = tempx;

	//delete it later, testing pointer sequences
	startChunk->nZPos->nZPos->nXPos->Setblock(0, 5, 5, 5);
	startChunk->nZPos->nZPos->nXPos->Setblock(0, 6, 5, 5);
	startChunk->nZPos->nZPos->nXPos->Update();

}

void World::Draw(Shader* program) {
	Chunk* tempx = startChunk;


	Chunk* temp = startChunk;
	for(int x = -DRAW_DISTANCE; x < DRAW_DISTANCE; x++) {
		temp = startChunk;


		for(int z = -DRAW_DISTANCE; z < DRAW_DISTANCE; z++) {

			startChunk->Draw(program);

			startChunk = startChunk->nXPos;

		}

		startChunk = temp;
		startChunk = startChunk->nZPos;
	}

	startChunk = tempx;

}

void World::UpdateChunk(int x, int y, int z) {
	Chunk* temp = startChunk;
	while( temp->GetPos().x != x / CHUNK_X){

		while( temp->GetPos().z != z / CHUNK_Z) {
			if(temp->nZPos) {
				temp = temp->nZPos;
			}
		}
		if(temp->nXPos) {
			temp = temp->nXPos;
		}
	}
	temp->Update();
}


//This doesn't work properly
void World::SetBlock(unsigned short int id, int x, int y, int z) {
	Chunk* temp = startChunk;

	for(int i = -DRAW_DISTANCE; i < x / CHUNK_X; i++) {

		for(int j = -DRAW_DISTANCE; j < z / CHUNK_Z; j++) {

			if(temp->nZPos) {
				temp = temp->nZPos;
			}
		}

		if(temp->nXPos) {
			temp = temp->nXPos;
		}
	}
	x %= CHUNK_X;
	y %= CHUNK_Y;
	z %= CHUNK_Z;
	std::cout << x << " " << y << " " << z << "\n";
	if(x < 0) {
		x = CHUNK_X + x;
	}
	if(z < 0) {
		z = CHUNK_Z + z;
	}
	std::cout << x << " " << y << " " << z << "\n";
	temp->Setblock(id, x, y, z);
	temp->Update();
}

Voxel* World::Get(int x, int y, int z) {

	Chunk* temp = startChunk;
	for(int i = -DRAW_DISTANCE; i < x / CHUNK_X; i++) {
		
		for(int j = -DRAW_DISTANCE; j < z / CHUNK_Z; j++) {
			if(temp->nZPos) {
				temp = temp->nZPos;
			}
		}
		if(temp->nXPos) {
			temp = temp->nXPos;
		}
	}

	return temp->Getblock(x % CHUNK_X, y % CHUNK_Y, z % CHUNK_Z);

}

Voxel* World::RayCast(glm::vec3 pos, glm::vec3 dir, float maxDist, glm::vec3& end, glm::vec3& norm, glm::vec3& iend) {
	float px = pos.x;
	float py = pos.y;
	float pz = pos.z;

	float dx = dir.x;
	float dy = dir.y;
	float dz = dir.z;

	float t = 0.0f;
	int ix = floor(px);
	int iy = floor(py);
	int iz = floor(pz);

	float stepx = (dx > 0.0f) ? 1.0f : -1.0f;
	float stepy = (dy > 0.0f) ? 1.0f : -1.0f;
	float stepz = (dz > 0.0f) ? 1.0f : -1.0f;

	float infinity = std::numeric_limits<float>::infinity();

	float txDelta = (dx == 0.0f) ? infinity : abs(1.0f / dx);
	float tyDelta = (dy == 0.0f) ? infinity : abs(1.0f / dy);
	float tzDelta = (dz == 0.0f) ? infinity : abs(1.0f / dz);

	float xdist = (stepx > 0) ? (ix + 1 - px) : (px - ix);
	float ydist = (stepy > 0) ? (iy + 1 - py) : (py - iy);
	float zdist = (stepz > 0) ? (iz + 1 - pz) : (pz - iz);

	float txMax = (txDelta < infinity) ? txDelta * xdist : infinity;
	float tyMax = (tyDelta < infinity) ? tyDelta * ydist : infinity;
	float tzMax = (tzDelta < infinity) ? tzDelta * zdist : infinity;

	int steppedIndex = -1;

	while(t <= maxDist) {
		Voxel* Voxel = Get(ix, iy, iz);
		if(Voxel == nullptr || Voxel->GetID()) {
			end.x = px + t * dx;
			end.y = py + t * dy;
			end.z = pz + t * dz;

			iend.x = ix;
			iend.y = iy;
			iend.z = iz;

			norm.x = norm.y = norm.z = 0.0f;
			if(steppedIndex == 0) norm.x = -stepx;
			if(steppedIndex == 1) norm.y = -stepy;
			if(steppedIndex == 2) norm.z = -stepz;
			return Voxel;
		}
		if(txMax < tyMax) {
			if(txMax < tzMax) {
				ix += stepx;
				t = txMax;
				txMax += txDelta;
				steppedIndex = 0;
			}
			else {
				iz += stepz;
				t = tzMax;
				tzMax += tzDelta;
				steppedIndex = 2;
			}
		}
		else {
			if(tyMax < tzMax) {
				iy += stepy;
				t = tyMax;
				tyMax += tyDelta;
				steppedIndex = 1;
			}
			else {
				iz += stepz;
				t = tzMax;
				tzMax += tzDelta;
				steppedIndex = 2;
			}
		}
	}
	iend.x = ix;
	iend.y = iy;
	iend.z = iz;

	end.x = px + t * dx;
	end.y = py + t * dy;
	end.z = pz + t * dz;
	norm.x = norm.y = norm.z = 0.0f;
	return nullptr;
}
