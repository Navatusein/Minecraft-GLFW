#include <iostream>

#include "World.h"

World::World(Texture* textureAtl) : textureAtlas(textureAtl) {
	for(int x = -DRAW_DISTANCE; x < DRAW_DISTANCE; x++) {
		for(int z = -DRAW_DISTANCE; z < DRAW_DISTANCE; z++) {
			Chunk* temp = new Chunk(textureAtl, x, 0, z);
			chunk_handler[x][z] = temp;
		}
	}
}

World::~World() {
	for(int x = -DRAW_DISTANCE; x < DRAW_DISTANCE; x++) {
	for(int z = -DRAW_DISTANCE; z < DRAW_DISTANCE; z++) {
		delete chunk_handler[x][z];
		chunk_handler[x].erase(z);
	}
	chunk_handler.erase(x);
}
}

void World::LoadChunk() {

}

void World::UnloadChunk() {
}

void World::GenerateChunk() {
	for(int x = -DRAW_DISTANCE; x < DRAW_DISTANCE; x++) {
		for(int z = -DRAW_DISTANCE; z < DRAW_DISTANCE; z++) {
			chunk_handler[x][z]->Fill();

			Chunk* neighbor[6];
			neighbor[0] = chunk_handler[x + 1][z];
			neighbor[1] = chunk_handler[x - 1][z];
			neighbor[2] = chunk_handler[x][z + 1];
			neighbor[3] = chunk_handler[x][z - 1];
			chunk_handler[x][z]->Update(neighbor);
		}
	}
}

void World::Draw(Shader* program) {
	for(int x = -DRAW_DISTANCE; x < DRAW_DISTANCE; x++) {
		for(int z = -DRAW_DISTANCE; z < DRAW_DISTANCE; z++) {
			chunk_handler[x][z]->Draw(program);
		}
	}
}

void World::UpdateChunk(int x, int y, int z) {

}

bool World::SetBlock(unsigned short int id, int x, int y, int z) {
	if(abs(x) / CHUNK_X > DRAW_DISTANCE || abs(z) / CHUNK_Z > DRAW_DISTANCE) {
		return 0;
	}
	Chunk*& temp = chunk_handler[x / CHUNK_X][z / CHUNK_Z];
	if(!temp) return 0;
	temp->Setblock(id, x % CHUNK_X, y % CHUNK_Y, z % CHUNK_Z);

	x /= CHUNK_X;
	z /= CHUNK_Z;

	Chunk* neighbor[6];
	neighbor[0] = chunk_handler[x + 1][z];
	neighbor[1] = chunk_handler[x - 1][z];
	neighbor[2] = chunk_handler[x][z + 1];
	neighbor[3] = chunk_handler[x][z - 1];
	temp->Update(neighbor);

	return 1;
}

Voxel* World::GetBlock(int x, int y, int z) {
	if(abs(x) / CHUNK_X > DRAW_DISTANCE || abs(z) / CHUNK_Z > DRAW_DISTANCE) {
		return nullptr;
	}
	Chunk* temp = chunk_handler[x / CHUNK_X][z / CHUNK_Z];
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
		Voxel* Voxel = GetBlock(ix, iy, iz);
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
