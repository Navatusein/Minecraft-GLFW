#pragma once

#include "../Graphic/Shader.h"
#include "../Mesh/Mesh.h"
#include "../Graphic/Texture.h"

class Voxel
{
private:
	unsigned int id;
public:
	Voxel();
	~Voxel();

	void Set(int id);
	int Get();








	struct Draw
	{
	private:
		Shader* program;
		int x, y, z;
		Texture* texture;
		Mesh side;
	public:
		Draw(Shader* program, int x, int y, int z) : program(program), x(x), y(y), z(z) {
			texture = CreateTexture("Resource/Textures/1.png");
			side.Construct(getPlane(), 6, texture);
		}
		float* getPlane() {
			float plane[] = {
				// x    y     z     u     v
			   -1.0f, 0.0f,-1.0f, 0.0f, 0.0f,
				1.0f, 0.0f,-1.0f, 1.0f, 0.0f,
			   -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,

				1.0f, 0.0f,-1.0f, 1.0f, 0.0f,
				1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			   -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			};
			return plane;
		}
		void XBack() {
			side.Center();
			side.Rotate(0.f, 0.f, -90.f);
			side.Move(-0.5f, 0.f, 0.f);
			side.Draw(program);
		};
		void XFront() {
			side.Center();
			side.Rotate(0.f, 0, -90.f);
			side.Move(0.5f, 0.f, 0.f);
			side.Draw(program);
		}
		void YBack() {
			side.Center();
			side.Rotate(-90.f, 0.f, 0.f);
			side.Move(0.f, -0.5f, 0.f);
			side.Draw(program);
		};
		void YFront() {
			side.Center();
			side.Rotate(90.f, 0.f, 0.f);
			side.Move(0.f, 0.5f, 0.f);
			side.Draw(program);
		}
		void ZBack() {
			side.Center();
			side.Move(0.f, 0.f, -0.5f);
			side.Draw(program);
		};
		void ZFront() {
			side.Center();
			side.Rotate(180.f, 0.f, 0.f);
			side.Move(0.f, 0.f, 0.5f);
			side.Draw(program);
		}
	};
};

