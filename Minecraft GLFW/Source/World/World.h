#pragma once

#include <map>

#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include "Chunk.h"

#include "../Graphic/Texture.h"
#include "../Graphic/Shader.h"

#define DRAW_DISTANCE 2

class World
{
private:
	std::map<long long, Chunk*> chunk_handler;

	Texture* textureAtlas;
public:
	World(Texture* textureAtl);
	~World();

	void LoadChunk();

	void UnloadChunk();

	void GenerateChunk();

	void Draw(Shader* program);

	void UpdateChunk(int x, int y, int z);

	bool SetBlock(unsigned short int id, int x, int y, int z);

	Voxel* GetBlock(int x, int y, int z);

	Voxel* RayCast(glm::vec3 pos, glm::vec3 dir, float maxDist, glm::vec3& end, glm::vec3& norm, glm::vec3& iend);

};

