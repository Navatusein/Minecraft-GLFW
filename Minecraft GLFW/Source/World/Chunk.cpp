#include <string>

#include "Chunk.h"
#include "../Mesh/Mesh.h"

Chunk::Chunk() {
}

Chunk::Chunk(const Chunk& val) : vox(val.vox), mesh(val.mesh), shard(val.shard), pos(val.pos) {
}

Chunk::Chunk(Texture* textureAtlas, int posx, int posy, int posz){
	mesh.Construct(CHUNK_W * CHUNK_H * CHUNK_W * 4 * 6, CHUNK_W * CHUNK_H * CHUNK_W * 6 * 6, textureAtlas);
	shard.Construct(&mesh);

	pos.x = posx;
	pos.y = posy;
	pos.z = posz;

	vox = new Voxel ***[CHUNK_W];
	for(int x = 0; x < CHUNK_W; x++) {
		vox[x] = new Voxel ** [CHUNK_H];
		for(int y = 0; y < CHUNK_H; y++) {
			vox[x][y] = new Voxel*[CHUNK_W];
			for(int z = 0; z < CHUNK_W; z++) {
				vox[x][y][z] = new Voxel(0);
			}
		}
	}

	generated = false;
	updated = true;

	mesh.Move(posx*CHUNK_W, posy*CHUNK_H, posz*CHUNK_W);
}



Chunk::~Chunk() {
	for(int x = 0; x < CHUNK_W; x++) {
		for(int y = 0; y < CHUNK_H; y++) {
			for(int z = 0; z < CHUNK_W; z++) {
				delete[]vox[x][y][z];
			}
			delete[]vox[x][y];
		}
		delete[]vox[x];
	}
	delete[]vox;
}

void Chunk::SetNeighbors(Neighbor* neighbor) {
	this->neighbor = neighbor;
}

void Chunk::DrawVox(postype x, postype y, postype z) {

	if(y + 1 < CHUNK_H) {
		if(vox[x][y + 1][z]->GetID() == 0) {
			shard.PushTop(vox[x][y][z]->GetRef(), x, y, z);
		}
	}
	else {
		if(neighbor->Top) {
			if(neighbor->Top->Getblock(x, 0, z)->GetID() == 0) {
				shard.PushTop(vox[x][y][z]->GetRef(), x, y, z);
			}
		}
	}

	if(y > 0) {
		if(vox[x][y - 1][z]->GetID() == 0) {
			shard.PushBottom(vox[x][y][z]->GetRef(), x, y, z);
		}
	}
	else {
		if(neighbor->Bottom) {
			if(neighbor->Bottom->Getblock(x, CHUNK_H - 1, z)->GetID() == 0) {                              //*TODO    somehow some voxel ids are garbage
				shard.PushBottom(vox[x][y][z]->GetRef(), x, y, z);                                                     //*this might cause a crash later
			}																																   
		}
	}

	if(x + 1 < CHUNK_W) {
		if(vox[x + 1][y][z]->GetID() == 0) {
			shard.PushXFront(vox[x][y][z]->GetRef(), x, y, z);
		}
	}
	else {
		if(neighbor->XFront) {
			if(neighbor->XFront->Getblock(0, y, z)->GetID() == 0) {
				shard.PushXFront(vox[x][y][z]->GetRef(), x, y, z);
			}
		}
	}

	if(x > 0) {
		if(vox[x - 1][y][z]->GetID() == 0) {
			shard.PushXRear(vox[x][y][z]->GetRef(), x, y, z);
			
		}
	}
	else {
		if(neighbor->XRear) {
			if(neighbor->XRear->Getblock(CHUNK_W-1, y, z)->GetID() == 0) {
				shard.PushXRear(vox[x][y][z]->GetRef(), x, y, z);
			}
		}
	}

	if(z + 1 < CHUNK_W) {
		if(vox[x][y][z + 1]->GetID() == 0) {
			shard.PushZFront(vox[x][y][z]->GetRef(), x, y, z);
		}
	}
	else {
		if(neighbor->ZFront) {
			if(neighbor->ZFront->Getblock(x, y, 0)->GetID() == 0) {
				shard.PushZFront(vox[x][y][z]->GetRef(), x, y, z);
			}
		}
	}

	if(z > 0) {

		if(vox[x][y][z - 1]->GetID() == 0) {
			shard.PushZRear(vox[x][y][z]->GetRef(), x, y, z);
		}
	}
	else {
		if(neighbor->ZRear) {
			if(neighbor->ZRear->Getblock(x, y, CHUNK_W - 1)->GetID() == 0) {
				shard.PushZRear(vox[x][y][z]->GetRef(), x, y, z);
			}
		}
	}


}

/*void Chunk::Update() {
	mesh.Clear();
	for(postype x = 0; x < CHUNK_W; x++) {
		for(postype y = 0; y < CHUNK_H; y++) {
			for(postype z = 0; z < CHUNK_W; z++) {
				if(vox[x][y][z]->GetID() != 0) {
					DrawVox(x, y, z);
				}
				else {
					if(x == 0) {
						if(neighbor->XRear) {
							if(neighbor->XRear->Getblock(CHUNK_W - 1, y, z)->GetID() != 0) {
								neighbor->XRear->DrawVox(CHUNK_W - 1, y, z);
								neighbor->XRear->UpdateMesh();
							}
						}
					}
					else if(x + 1 == CHUNK_W) {
						if(neighbor->XFront) {
							if(neighbor->XFront->Getblock(0, y, z)->GetID() != 0) {
								neighbor->XFront->DrawVox(0, y, z);
								neighbor->XFront->UpdateMesh();
							}
						}
					}
					if(y == 0) {
						if(neighbor->Bottom) {
							if(neighbor->Bottom->Getblock(x, CHUNK_H - 1, z)->GetID() != 0) {
								neighbor->Bottom->DrawVox(x, CHUNK_H - 1, z);
								neighbor->Bottom->UpdateMesh();
							}
						}
					}
					else if(y + 1 == CHUNK_H) {
						if(neighbor->Top) {
							if(neighbor->Top->Getblock(x, 0, z)->GetID() != 0) {
								neighbor->Top->DrawVox(x, 0, z);
								neighbor->Top->UpdateMesh();
							}
						}
					}
					if(z == 0) {
						if(neighbor->ZRear) {
							if(neighbor->ZRear->Getblock(x, y, CHUNK_W - 1)->GetID() != 0) {
								neighbor->ZRear->DrawVox(x, y, CHUNK_W - 1);
								neighbor->ZRear->UpdateMesh();
							}
						}
					}
					else if(z + 1 == CHUNK_W) {
						if(neighbor->ZFront) {
							if(neighbor->ZFront->Getblock(x, y, 0)->GetID() != 0) {
								neighbor->ZFront->DrawVox(x, y, 0);
								neighbor->ZFront->UpdateMesh();
							}
						}
					}
				}
			}
		}
	}

	mesh.UpdateMesh();
	updated = true;
}*/

void Chunk::UpdateMesh() {
	mesh.UpdateMesh();
}

void Chunk::Draw(Shader* program) {
	mesh.Draw(program);
}

void Chunk::Fill() {
	for(postype x = 0; x < CHUNK_W; x++) {
		for(postype y = 0; y < CHUNK_H; y++) {
			for(postype z = 0; z < CHUNK_W; z++) {
				if(y == 7) {
					vox[x][y][z]->Set(1);
				}
				else if(y == 15) {
					vox[x][y][z]->Set(3);
				}
				else if(y >= 5 && y < 7){
					vox[x][y][z]->Set(3);
				}
				else if(y < 5) {
					vox[x][y][z]->Set(4);
				}
				else {
					vox[x][y][z]->Set(0);
				}
			}
		}
	}
}

void Chunk::Setblock(unsigned short int id, postype x, postype y, postype z) {
	if(y >= CHUNK_H) {
		//std::cerr << "chunk y limit has been overflowed\n";
		return;
	}
	vox[x][y][z]->Set(id);
}

void Chunk::Setblock_u(unsigned short int id, postype x, postype y, postype z) {
	if(y >= CHUNK_H) {
		//std::cerr << "chunk y limit has been overflowed\n";
		return;
	}
		vox[x][y][z]->Set(id);

		if(id == 0) {
			if(x == 0) {
				if(neighbor->XRear) {
					if(neighbor->XRear->Getblock(CHUNK_W - 1, y, z)->GetID() != 0) {
						neighbor->XRear->DrawVox(CHUNK_W - 1, y, z);
						neighbor->XRear->UpdateMesh();
					}
				}
			}
			else if(x + 1 == CHUNK_W) {
				if(neighbor->XFront) {
					if(neighbor->XFront->Getblock(0, y, z)->GetID() != 0) {
						neighbor->XFront->DrawVox(0, y, z);
						neighbor->XFront->UpdateMesh();
					}
				}
			}
			if(y == 0) {
				if(neighbor->Bottom) {
					if(neighbor->Bottom->Getblock(x, CHUNK_H - 1, z)->GetID() != 0) {
						neighbor->Bottom->DrawVox(x, CHUNK_H - 1, z);
						neighbor->Bottom->UpdateMesh();
					}
				}
			}
			else if(y + 1 == CHUNK_H) {
				if(neighbor->Top) {
					if(neighbor->Top->Getblock(x, 0, z)->GetID() != 0) {
						neighbor->Top->DrawVox(x, 0, z);
						neighbor->Top->UpdateMesh();
					}
				}
			}
			if(z == 0) {
				if(neighbor->ZRear) {
					if(neighbor->ZRear->Getblock(x, y, CHUNK_W - 1)->GetID() != 0) {
						neighbor->ZRear->DrawVox(x, y, CHUNK_W - 1);
						neighbor->ZRear->UpdateMesh();
					}
				}
			}
			else if(z + 1 == CHUNK_W) {
				if(neighbor->ZFront) {
					if(neighbor->ZFront->Getblock(x, y, 0)->GetID() != 0) {
						neighbor->ZFront->DrawVox(x, y, 0);
						neighbor->ZFront->UpdateMesh();
					}
				}
			}
		}
		else {
			if(x == 0) {
				if(neighbor->XRear) {
					neighbor->XRear->updated = false;
				}
			}
			else if(x + 1 == CHUNK_W) {
				if(neighbor->XFront) {
					neighbor->XFront->updated = false;
					}
				}
			}
			if(y == 0) {
				if(neighbor->Bottom) {
					neighbor->Bottom->updated = false;
				}
			}
			else if(y + 1 == CHUNK_H) {
				if(neighbor->Top) {
					neighbor->Top->updated = false;
				}
			}
			if(z == 0) {
				if(neighbor->ZRear) {
					neighbor->ZRear->updated = false;
				}
			}
			else if(z + 1 == CHUNK_W) {
				if(neighbor->ZFront) {
					neighbor->ZFront->updated = false;
				}
			}
}

Voxel* Chunk::Getblock(postype x, postype y, postype z) {
	if(this) {
		return vox[x][y][z]->GetRef();
	}
	else return nullptr;
}

glm::vec3 Chunk::GetPos() {
	return pos;
}


void UpdateChunk(Chunk& chunk) {
	chunk.mesh.Clear();
	for(postype x = 0; x < CHUNK_W; x++) {
		for(postype y = 0; y < CHUNK_H; y++) {
			for(postype z = 0; z < CHUNK_W; z++) {
				if(chunk.vox[x][y][z]->GetID() != 0) {
					chunk.DrawVox(x, y, z);
				}
			}
		}
	}

	chunk.mesh.UpdateMesh();
	chunk.updated = true;
}
