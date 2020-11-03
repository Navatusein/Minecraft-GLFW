#pragma once
class Voxel
{
private:
	unsigned int id;
public:
	Voxel();
	~Voxel();

	void Set(int id);
	int Get();
};

