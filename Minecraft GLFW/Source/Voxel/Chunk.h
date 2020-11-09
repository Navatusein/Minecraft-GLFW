#pragma once
#include "Voxel.h"
#include "../Graphic/Shader.h"

#include "../Mesh/BigMesh.h"
#include "../Mesh/ShardMesh.h"

#define CHUNK_X 16
#define CHUNK_Y 16
#define CHUNK_Z 16


class Chunk
{
private:
	Voxel*** vox;
	void DrawVox(postype x, postype y, postype z, Chunk* neighbour[6]);

	BigMesh mesh;
	ShardMesh shard;

	glm::vec3 pos;

public:
	Chunk();
	Chunk(const Chunk& val);
	Chunk(Texture* textureAtlas, int posx, int posy, int posz);
	~Chunk();

	void Update(Chunk* neighbour[6]);

	void Draw(Shader* program);

	void Fill();

	void Setblock(unsigned short int id, postype x, postype y, postype z);

	Voxel* Getblock(postype x, postype y, postype z);

	glm::vec3 GetPos();
};

