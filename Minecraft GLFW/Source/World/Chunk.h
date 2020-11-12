#pragma once
#include "Voxel.h"
#include "../Graphic/Shader.h"

#include "../Mesh/BigMesh.h"
#include "../Mesh/ShardMesh.h"

#include "Container/Neighbor.h"

#define CHUNK_X 16
#define CHUNK_Y 16
#define CHUNK_Z 16


class Chunk
{
private:
	Voxel**** vox;

	BigMesh mesh;
	ShardMesh shard;

	glm::vec3 pos;
public:
	Neighbor* neighbor;

public:
	Chunk();
	Chunk(const Chunk& val);
	Chunk(Texture* textureAtlas, int posx, int posy, int posz);
	~Chunk();
	void DrawVox(postype x, postype y, postype z);

	void SetNeighbors(Neighbor* neighbor);

	void Update();

	void UpdateMesh();

	void Draw(Shader* program);

	void Fill();

	void Setblock(unsigned short int id, postype x, postype y, postype z);

	Voxel* Getblock(postype x, postype y, postype z);

	glm::vec3 GetPos();
};

