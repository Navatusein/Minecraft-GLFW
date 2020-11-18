#include <iostream>
#include <thread>
#include <chrono>

#include "World.h"
#include "Container/Neighbor.h"
#include "ChunkGeneration.h"

World::World(Texture* textureAtl, long seed) : textureAtlas(textureAtl) {
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	// initializing chunks
	for(int x = -H_DRAW_DISTANCE; x < H_DRAW_DISTANCE; x++) {
		for(short y = -V_DRAW_DISTANCE; y < V_DRAW_DISTANCE; y++) {
			for(int z = -H_DRAW_DISTANCE; z < H_DRAW_DISTANCE; z++) {
				Chunk* temp = new Chunk(textureAtl, x, y, z);
				long long index = x + z * pow(2, 24) + y * pow(2, 48);
				chunk_handler[index] = temp;
			}
		}
	}

	// setting the neighbors for our initialized chunks
	for(int x = -H_DRAW_DISTANCE; x < H_DRAW_DISTANCE; x++) {
		for(short y = -V_DRAW_DISTANCE; y < V_DRAW_DISTANCE; y++) {
			for(int z = -H_DRAW_DISTANCE; z < H_DRAW_DISTANCE; z++) {
				Neighbor* temp = new Neighbor;
				long long index = x + z * pow(2, 24) + y * pow(2, 48);
				long long tempIndex = (x + 1) + z * pow(2, 24) + y * pow(2, 48);
				temp->XFront = chunk_handler[tempIndex];
				tempIndex = (x - 1) + z * pow(2, 24) + y * pow(2, 48);
				temp->XRear = chunk_handler[tempIndex];
				tempIndex = x + (z + 1) * pow(2, 24) + y * pow(2, 48);
				temp->ZFront = chunk_handler[tempIndex];
				tempIndex = x + (z - 1) * pow(2, 24) + y * pow(2, 48);
				temp->ZRear = chunk_handler[tempIndex];
				tempIndex = x + z * pow(2, 24) + (y + 1) * pow(2, 48);
				temp->Top = chunk_handler[tempIndex];
				tempIndex = x + z * pow(2, 24) + (y - 1) * pow(2, 48);
				temp->Bottom = chunk_handler[tempIndex];
				chunk_handler[index]->SetNeighbors(temp);
			}
		}
	}
}

World::~World() {
	for(int x = -H_DRAW_DISTANCE; x < H_DRAW_DISTANCE; x++) {
		for(short y = -V_DRAW_DISTANCE; y < V_DRAW_DISTANCE; y++) {
			for(int z = -H_DRAW_DISTANCE; z < H_DRAW_DISTANCE; z++) {
				long long index = x + z * pow(2, 24) + y * pow(2, 48);
				delete chunk_handler[index];
				chunk_handler.erase(index);
			}
		}
	}
}

void World::LoadChunk() {
	//todo
}

void World::UnloadChunk() {
	//todo
}

void World::Draw(Shader* program) {

	for(int x = -H_DRAW_DISTANCE; x < H_DRAW_DISTANCE; x++) {
		for(short y = -V_DRAW_DISTANCE; y < V_DRAW_DISTANCE; y++) {
			for(int z = -H_DRAW_DISTANCE; z < H_DRAW_DISTANCE; z++) {
				long long index = x + z * pow(2, 24) + y * pow(2, 48);

				Chunk& temp = *chunk_handler[index];

				//updates every chunk that has been modified
				if(!chunk_handler[index]->updated) {
					UpdateChunk(temp);	// this is temporary, as soon as next code will be working properly, this line has to be removed
					/*try {
						std::future_status status;
						status = fut_1.wait_for(std::chrono::microseconds(0));
						if(status == std::future_status::ready) {
							fut_1.get();
							fut_1 = std::async(std::launch::async, &UpdateChunk, std::ref(*chunk_handler[index]));
						}
					}
					catch(const std::future_error) { //this will occur if fut hasn't been initialized yet
						fut_1 = std::async(std::launch::async, &UpdateChunk, std::ref(*chunk_handler[index]));
					}*/
				}

				//generates ungenerated chunks
				if(!chunk_handler[index]->generated) {
					try {
						std::future_status status;
						status = fut.wait_for(std::chrono::microseconds(0));
						if(status == std::future_status::ready) {
							fut.get();
							fut = std::async(std::launch::async, &GenerateChunk, std::ref(temp), x, y, z);
						}
					}
					catch(const std::future_error) { //this will occur if fut hasn't been initialized yet
						fut = std::async(std::launch::async, &GenerateChunk, std::ref(temp), x, y, z);
					}
				}

				//draw cycle
				else if(chunk_handler[index]->updated) {
					chunk_handler[index]->Draw(program);
				}
				
				
			}
		}
	}
}

// foo that updates every loaded chunk
void World::UpdateChunks() {
	for(int x = -H_DRAW_DISTANCE; x < H_DRAW_DISTANCE; x++) {
		for(short y = -V_DRAW_DISTANCE; y < V_DRAW_DISTANCE; y++) {
			for(int z = -H_DRAW_DISTANCE; z < H_DRAW_DISTANCE; z++) {
				long long index = x + z * pow(2, 24) + y * pow(2, 48);
				chunk_handler[index]->updated = false;
			}
		}
	}
}

bool World::SetBlock(unsigned short int id, int x, int y, int z) {
	if(abs(x) / CHUNK_W > H_DRAW_DISTANCE || abs(z) / CHUNK_W > H_DRAW_DISTANCE || abs(y) / CHUNK_H > V_DRAW_DISTANCE) {
		return 0;
	}

	int xc, yc, zc; // chunk position temp variables
	xc = x; yc = y; zc = z;



	// normalizing coordinates
	if(xc < 0) {
		xc /= CHUNK_W;
		xc -= 1;
		x = abs(abs(x) % CHUNK_W - CHUNK_W);
	}
	else {
		xc /= CHUNK_W;
		x = abs(x) % CHUNK_W;
	}

	if(yc < 0) {
		yc /= CHUNK_H;
		yc -= 1;
		y = abs(abs(y) % CHUNK_H - CHUNK_H);
	}
	else {
		yc /= CHUNK_H;
		y = abs(y) % CHUNK_H;
	}

	if(zc < 0) {
		zc /= CHUNK_W;
		zc -= 1;
		z = abs(abs(z) % CHUNK_W - CHUNK_W);
	}
	else {
		zc /= CHUNK_W;
		z = abs(z) % CHUNK_W;
	}

	//normalizing block coordinates
	if(x == CHUNK_W) {
		x = 0;
		xc += 1;
	}
	if(y == CHUNK_H) {
		y = 0;
		yc += 1;
	}
	if(z == CHUNK_W) {
		z = 0;
		zc += 1;
	}

	long long index = xc + zc * pow(2, 24) + yc * pow(2, 48);
	Chunk*& temp = chunk_handler[index];

	if(!temp) return 0;
	temp->Setblock(id, x, y, z);
	temp->updated = 0;

	return 1;
}

Voxel* World::GetBlock(int x, int y, int z) {
	if(abs(x) / CHUNK_W > H_DRAW_DISTANCE || abs(z) / CHUNK_W > H_DRAW_DISTANCE || abs(y) / CHUNK_H > V_DRAW_DISTANCE) {
		return 0;
	}

	int xc, yc, zc; // chunk position temp variables
	xc = x; yc = y; zc = z;

	// normalizing coordinates
	if(xc < 0) {
		xc /= CHUNK_W;
		xc -= 1;
		x = abs(abs(x) % CHUNK_W - CHUNK_W);
	}
	else {
		xc /= CHUNK_W;
		x = abs(x) % CHUNK_W;
	}

	if(yc < 0) {
		yc /= CHUNK_H;
		yc -= 1;
		y = abs(abs(y) % CHUNK_H - CHUNK_H);
	}
	else {
		yc /= CHUNK_H;
		y = abs(y) % CHUNK_H;
	}

	if(zc < 0) {
		zc /= CHUNK_W;
		zc -= 1;
		z = abs(abs(z) % CHUNK_W - CHUNK_W);
	}
	else {
		zc /= CHUNK_W;
		z = abs(z) % CHUNK_W;
	}
	//normalizing block coordinates
	if(x == CHUNK_W) {
		x = 0;
		xc += 1;
	}
	if(y == CHUNK_H) {
		y = 0;
		yc += 1;
	}
	if(z == CHUNK_W) {
		z = 0;
		zc += 1;
	}


	long long index = xc + zc * pow(2, 24) + yc * pow(2, 48);
	Chunk*& temp = chunk_handler[index];
	if(!temp) return nullptr;

	return temp->Getblock(x, y, z);
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
