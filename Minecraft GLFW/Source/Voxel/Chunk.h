#pragma once
#include "Voxel.h"
#include "../Graphic/Shader.h"

#include "../Mesh/BigMesh.h"
#include "../Mesh/ShardMesh.h"

#define CHUNK_X 8
#define CHUNK_Y 8
#define CHUNK_Z 8


class Chunk
{
private:
	Voxel*** vox;
	void DrawVox(postype x, postype y, postype z);

	BigMesh mesh;
	ShardMesh shard;

	glm::vec3 pos;

public:
	//Chunk(Texture* textureAtlas);
	Chunk(Texture* textureAtlas, int posx, int posy, int posz);
	~Chunk();

	void Update();

	void Draw(Shader* program);

	void Fill();

	void Setblock(unsigned short int id, postype x, postype y, postype z);

	Voxel* Getblock(postype x, postype y, postype z);

	glm::vec3 GetPos();


	Chunk* nTop;      // Neighboring chunk Top
	Chunk* nBottom;// Neighboring chunk Bottom
	Chunk* nXPos;	  // Neighboring chunk Right
	Chunk* nXNeg;	  // Neighboring chunk Left
	Chunk* nZPos;	  // Neighboring chunk Front
	Chunk* nZNeg;	  // Neighboring chunk Rear
};

