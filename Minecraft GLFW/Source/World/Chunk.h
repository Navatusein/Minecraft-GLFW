#pragma once

#include "Voxel.h"
#include "../Graphic/Shader.h"

#include "../Mesh/BigMesh.h"
#include "../Mesh/ShardMesh.h"

#include "Container/Neighbor.h"

#define CHUNK_W 32
#define CHUNK_H 32

#define CHUNK_X CHUNK_W
#define CHUNK_Y CHUNK_H
#define CHUNK_Z CHUNK_W


class Chunk
{
private:
	Voxel**** vox;

	BigMesh mesh;
	ShardMesh shard;

	glm::vec3 pos;

public:
	bool generated;
	bool updated; // flag for chunk to be udpated
	bool updating; // flag for draw function not to draw a chunks that is updating
	Neighbor* neighbor; // pointers to neighboring chunks

public:
	
	Chunk();
	Chunk(const Chunk& val);
	Chunk(Texture* textureAtlas, int posx, int posy, int posz);
	~Chunk();
	void DrawVox(postype x, postype y, postype z);

	void SetNeighbors(Neighbor* neighbor);

	void UpdateMesh();

	void Draw(Shader* program);

	void Fill();

	void Setblock(unsigned short int id, postype x, postype y, postype z);
	void Setblock_u(unsigned short int id, postype x, postype y, postype z);

	Voxel* Getblock(postype x, postype y, postype z);

	glm::vec3 GetPos();

	friend void UpdateChunk(Chunk& chunk);
};
void UpdateChunk(Chunk& chunk);

