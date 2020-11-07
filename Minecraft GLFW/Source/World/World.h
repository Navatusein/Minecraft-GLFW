#pragma once

#include "../Voxel/Chunk.h"

#include "../Graphic/Texture.h"
#include "../Graphic/Shader.h"

#define DRAW_DISTANCE 5

class World
{
private:
	//Chunk* playerChunk;
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

};

