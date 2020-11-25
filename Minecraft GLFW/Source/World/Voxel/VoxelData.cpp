#include "VoxelData.h"

VoxelData::VoxelData(std::string fileName) {
	std::ifstream fin("Resourse/Blocks/" + fileName + ".block");

	if (!fin.is_open()) {
		throw Mexception("[VoxelData] Error open block file: " + fileName);
	}

	

	bool DifferentSide;

	unsigned char AllRead = 0;

	std::string Line;

	while (std::getline(fin, Line)) {
		if (Line == "ID") {
			unsigned short id;
			fin >> id;
			Data.ID = static_cast<BlocksID>(id);
			AllRead++;
		}
		else if (Line == "BlockType") {
			unsigned char type;
			fin >> type;
			Data.BlockType = static_cast<BlockTypes>(type);
			AllRead++;
		}
		else if (Line == "DifferentSide") {
			fin >> DifferentSide;
			if (DifferentSide) {
				Data.textures = new SideTexture[3];
			}
			else {
				Data.textures = new SideTexture;
			}
			AllRead++;
		}
		else if (!DifferentSide && Line == "Textures") {
			AllRead++;
		}
		else if (DifferentSide && Line == "TextureUpSide") {
			unsigned short Tbegin;
			unsigned char Tcount;

			fin >> Tbegin;
			fin >> Tcount;

			Data.textures[1] = { Tbegin, Tcount };
			AllRead++;
		}
		else if (DifferentSide && Line == "TextureDownSide") {
			unsigned short Tbegin;
			unsigned char Tcount;

			fin >> Tbegin;
			fin >> Tcount;

			Data.textures[2] = { Tbegin, Tcount };
			AllRead++;
		}
		else if (DifferentSide && Line == "TextureSide") {
			unsigned short Tbegin;
			unsigned char Tcount;

			fin >> Tbegin;
			fin >> Tcount;

			Data.textures[3] = { Tbegin, Tcount };
			AllRead++;
		}
		else if (Line == "Opaque") {
			bool Opaque;

			fin >> Opaque;

			Data.isOpaque = Opaque;

			AllRead++;
		}
		else if (DifferentSide && Line == "Collidable") {
			bool Collidable;

			fin >> Collidable;

			Data.isCollidable = Collidable;

			AllRead++;
		}
	}

	fin.close();

	if ((AllRead != 8 && DifferentSide) || (AllRead != 6 && !DifferentSide)) {
		throw Mexception("[VoxelData] Error block file read: " + fileName);
	}

}

const BlockData& VoxelData::getData() {
	return Data;
}

VoxelData::~VoxelData() {
	delete[]Data.textures;
}
