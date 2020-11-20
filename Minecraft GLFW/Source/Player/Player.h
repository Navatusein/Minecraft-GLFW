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

#define TERMINAL_VELOCITY 150 // determines maximum freefall speed

class Player : public Entity {
private:
	Camera* camera;

	World* world;

	AABB HitBox;

	float Speed;
	float JumpForce;

	float pitch;
	float yaw;

	float FOV;
	float renderDist;

	bool isFlying;
	bool isFlyOn;

	void MouseUpdate();

	void KeyBoardUpdate();

	void CheckCollision();

	void PhysicUpdate();

	void CollisionTest();
public:
	Player(World* world);

	
	void Update();
	
	

	Camera* getCamera();

	~Player();

};

