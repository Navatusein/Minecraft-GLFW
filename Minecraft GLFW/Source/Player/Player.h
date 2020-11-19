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

class Player : public Entity {
private:
	Camera* camera;

	World* world;

	AABB HitBox;

	vec3 Velocity;

	float LastTime;
	float Delta;

	float Speed;

	float pitch;
	float yaw;

	float FOV;
	float renderDist;

	bool isOnGround;
	bool isFluing;

	bool isFlyOn;

	void CollisionTest(const vec3& Velocity_);

public:
	Player(World* world);

	void CheckCollision();

	void KeyBoardUpdate();
	void MouseUpdate();

	Camera* getCamera();

	~Player();

};

