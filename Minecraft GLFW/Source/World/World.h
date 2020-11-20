#pragma once

#include <map>
#include <future>

#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include <FastNoiseLite.h>

#include "Chunk.h"

#include "../Physics/AABB.h"

#include "../Graphic/Texture.h"
#include "../Graphic/Shader.h"

#define H_DRAW_DISTANCE 2
#define V_DRAW_DISTANCE 1

#define GRAVITY 9.8

class World
{
private:
	std::map<long long, Chunk*> chunk_handler;

	Texture* textureAtlas;

	FastNoiseLite noise;

	std::future<Chunk*> fut;
	std::future<void> fut_1;
public:
	World(Texture* textureAtl, long seed);
	~World();

	void LoadChunk();

	void UnloadChunk();

	//void GenerateChunk(int x_chunk, int y_chunk, int z_chunk);

	void Draw(Shader* program);

	void UpdateChunks();

	bool SetBlock(unsigned short int id, int x, int y, int z);
	bool SetBlock_u(unsigned short int id, int x, int y, int z);

	Voxel* GetBlock(int x, int y, int z);
	bool GetObstruction(float x, float y, float z);

	Voxel* RayCast(glm::vec3 pos, glm::vec3 dir, float maxDist, glm::vec3& end, glm::vec3& norm, glm::vec3& iend);

	AABB getBlockAABB(const glm::vec3 Pos);
};

