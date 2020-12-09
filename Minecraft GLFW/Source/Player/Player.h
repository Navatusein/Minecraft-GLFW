#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../Entity/Entity.h"

#include "../Window/Window.h"
#include "../Window/Camera.h"
#include "../Window/Events.h"

#include "../ErrorHandling.h"

#include "../Physics/AABB.h"

#include "../World/World.h"

#include "../Graphic/Shader.h"

#include "../World/Voxel/VoxelDataBase.h"

#include "PlayerGUI.h"

#define TERMINAL_VELOCITY 150 // determines maximum freefall speed

class Player : public Entity {
private:
	Camera* camera;

	World* world;

	AABB HitBox;

	PlayerGUI* pGUI;

	F3menu F3menuData;

	unsigned short FPSCounter;

	float Speed;
	float JumpForce;

	float pitch;
	float yaw;

	float FOV;
	float FOVSettings;
	float renderDist;
	float LastFPSTime;

	bool isFlying;
	bool isFlyOn;

public:
	Player(World* world, PlayerGUI* pGUI);

	
	void Update();
	
	void DrawGUI(Shader* program);

	Camera* getCamera();

	~Player();

private:
	void MouseUpdate();

	void KeyBoardUpdate();

	void CheckCollision();

	void PhysicUpdate();

	void CollisionTest();

	void ScrollUpdate();

};

