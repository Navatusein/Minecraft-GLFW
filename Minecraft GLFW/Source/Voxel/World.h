#pragma once

#include "Chunk.h"

class World
{
private:
	Chunk*** chunk;
public:
	World();
	~World();

	void LoadChunk();

	void UnloadChunk();

	void GenerateChunk();

};

