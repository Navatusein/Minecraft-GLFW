#pragma once
#include <FastNoiseLite.h>
#include <thread>
#include <iostream>
#include "chunk.h"


Chunk* GenerateChunk(Chunk& chunk, int x_chunk, int y_chunk, int z_chunk) {
	/*
	* CHUNK GENERATION ALGORITHM
	* PLAY WITH IT AS YOU WISH
	*
	*/
	//long long index = x_chunk + z_chunk * pow(2, 24) + y_chunk * pow(2, 48);

	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
	float frequency[3] = { 0.3, 1, 3 };
	float magnitude[3] = { 30, 6, 2 };

	for(int x_voxel = 0; x_voxel < CHUNK_X; x_voxel++) {
		float x_key = x_voxel + x_chunk * CHUNK_X;
		for(int z_voxel = 0; z_voxel < CHUNK_Z; z_voxel++) {
			float z_key = z_voxel + z_chunk * CHUNK_Z;
			float temp[3];
			for(int i = 0; i < 3; i++) {
				temp[i] = noise.GetNoise(x_key * frequency[i], z_key * frequency[i]);
			} 
			float final = 0;
			for(int i = 0; i < 3; i++) {
				final += temp[i] * magnitude[i];
			}

			final -= y_chunk * CHUNK_H;
			//std::cout << final << "\n";
			if(final < CHUNK_H) {
				if(final >= 0) {
					chunk.Setblock(1, x_voxel, (int)final, z_voxel);
				}
				
				//final = CHUNK_H;
				
			}
			for(int i = final - 1; i >= 0; i--) {
				if(i >= 0) {
					chunk.Setblock(3, x_voxel, i, z_voxel);
				}
			}
		}
	}
	chunk.generated = true;
	chunk.updated = false;
	return &chunk;
}