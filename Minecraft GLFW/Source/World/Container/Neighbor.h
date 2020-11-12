#pragma once
class Chunk;

struct Neighbor
{
	Chunk* Top;
	Chunk* Bottom;
	Chunk* XFront;
	Chunk* XRear;
	Chunk* ZFront;
	Chunk* ZRear;

	Neighbor();

	Neighbor(Chunk* Top, Chunk* Bottom, Chunk* XFront, Chunk* XRear, Chunk* ZFront, Chunk* ZRear);
};

