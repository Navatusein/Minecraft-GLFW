#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../Window/Window.h"
#include "../Window/Camera.h"
#include "../Window/Events.h"


#include "../World/World.h"

class Player {
private:
	Camera* camera;

	World* world;

	float LastTime;
	float Delta;

	float CamX;
	float CamY;

	float Speed;

	float FOV;
	float renderDist;
public:
	Player(World* world);

	void KeyBoardUpdate();

	Camera* getCamera();

	~Player();

};

