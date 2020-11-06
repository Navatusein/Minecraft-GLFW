#pragma once
#include "Voxel.h"
#include "../Graphic/Shader.h"

#include "../Mesh/BigMesh.h"
#include "../Mesh/ShardMesh.h"

#define CHUNK_X 32
#define CHUNK_Y 32
#define CHUNK_Z 32


class Chunk
{
private:
	Voxel*** vox;
	void DrawVox(postype x, postype y, postype z);

	BigMesh mesh;
	ShardMesh shard;
public:
	Chunk(Texture* textureAtlas);
	~Chunk();

	void Update();

	void Draw(Shader* program);

	void Fill();
};

