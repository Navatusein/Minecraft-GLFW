#include "VoxelRenderer.h"

#define VERTEX_SIZE (3 + 2 + 1)

#define CDIV(X,A) (((X) < 0) ? ((X) / (A) - 1) : ((X) / (A)))
#define LOCAL_NEG(X, SIZE) (((X) < 0) ? ((SIZE)+(X)) : (X))
#define LOCAL(X, SIZE) ((X) >= (SIZE) ? ((X) - (SIZE)) : LOCAL_NEG(X, SIZE))
#define IS_CHUNK(X,Y,Z) (GET_CHUNK(X,Y,Z) != nullptr)
#define GET_CHUNK(X,Y,Z) (chunks[((CDIV(Y, ChunkH)+1) * 3 + CDIV(Z, ChunkD) + 1) * 3 + CDIV(X, ChunkW) + 1])

#define VOXEL(X,Y,Z) (GET_CHUNK(X,Y,Z)->Voxels[(LOCAL(Y, ChunkH) * ChunkD + LOCAL(Z, ChunkD)) * ChunkW + LOCAL(X, ChunkW)])
#define IS_BLOCKED(X,Y,Z) ((!IS_CHUNK(X, Y, Z)) || VOXEL(X, Y, Z).id)

#define VERTEX(INDEX, X,Y,Z, U,V, L) buffer[INDEX+0] = (X);\
								  buffer[INDEX+1] = (Y);\
								  buffer[INDEX+2] = (Z);\
								  buffer[INDEX+3] = (U);\
								  buffer[INDEX+4] = (V);\
								  buffer[INDEX+5] = (L);\
								  INDEX += VERTEX_SIZE;

int chunk_attrs[] = { 3,2,1, 0 };

VoxelRenderer::VoxelRenderer(size_t capacity) : capacity(capacity) {
	CONSOLWRITE("buffer");
	buffer = new float[capacity * VERTEX_SIZE * 6];
	
}

VoxelRenderer::~VoxelRenderer() {
	delete[] buffer;
}

Mesh* VoxelRenderer::render(Chunk* chunk, const Chunk** chunks) {
	size_t index = 0;
	for (int y = 0; y < ChunkH; y++) {
		for (int z = 0; z < ChunkD; z++) {
			for (int x = 0; x < ChunkW; x++) {
				Voxel vox = chunk->Voxels[(y * ChunkD + z) * ChunkW + x];
				unsigned int id = vox.id;

				if (!id) {
					continue;
				}

				float l;
				float uvsize = 1.0f / 16.0f;
				float u = (id % 16) * uvsize;
				float v = 1 - ((1 + id / 16) * uvsize);

				if (!IS_BLOCKED(x, y + 1, z)) {
					l = 1.0f;
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v, l);
				}
				if (!IS_BLOCKED(x, y - 1, z)) {
					l = 0.75f;
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v + uvsize, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
				}

				if (!IS_BLOCKED(x + 1, y, z)) {
					l = 0.95f;
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u, v, l);
				}
				if (!IS_BLOCKED(x - 1, y, z)) {
					l = 0.85f;
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u, v, l);
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
				}

				if (!IS_BLOCKED(x, y, z + 1)) {
					l = 0.9f;
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, u, v + uvsize, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, u, v, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, u + uvsize, v, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, u + uvsize, v + uvsize, l);
				}
				if (!IS_BLOCKED(x, y, z - 1)) {
					l = 0.8f;
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, u + uvsize, v + uvsize, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, u + uvsize, v, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, u, v + uvsize, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, u, v, l);
				}
			}
		}
	}
	return new Mesh(buffer, index / VERTEX_SIZE, chunk_attrs);
}