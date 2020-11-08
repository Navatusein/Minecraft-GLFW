#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include "../Voxel/Chunk.h"

#include "../Graphic/Texture.h"
#include "../Graphic/Shader.h"

#define DRAW_DISTANCE 2

class World
{
private:
	Chunk* playerChunk;
	Chunk* startChunk;
	Texture* textureAtlas;

	int xPos;
	int yPos;
	int zPos;
public:
	World(Texture* textureAtl);
	~World();

	void LoadChunk();

	void UnloadChunk();

	void GenerateChunk();

	void Draw(Shader* program);

	void UpdateChunk(int x, int y, int z);

	void SetBlock(unsigned short int id, int x, int y, int z);

	Voxel* Get(int x, int y, int z);

	Voxel* RayCast(glm::vec3 pos, glm::vec3 dir, float maxDist, glm::vec3& end, glm::vec3& norm, glm::vec3& iend);

};

