#include "Player.h"

const vec3 Dimensions(0.3, 1.5, 0.3);


Player::Player(World* world, PlayerGUI* pGUI) :HitBox(Dimensions), world(world), pGUI(pGUI) {
	
	Position = {5, 16, 5};

	FOVSettings = 100.f;
	renderDist = 10000.f;
	camera = new Camera(&Position, &View, &FOV, renderDist);

	yaw = 90;
	pitch = 0;

	LastTime = glfwGetTime();
	LastFPSTime = glfwGetTime();
	Delta = 0.0f;

	FPSCounter = 0;

	Speed = 5;
	JumpForce = 7.5;

	isFlying = false;
	isFlyOn = false; // this doesn't seem to be used
	isOnGround = false;

	pGUI->SetF3MenuData(&F3menuData);
}

void Player::Update() {
	KeyBoardUpdate();
	PhysicUpdate();
	CheckCollision();
}

void Player::DrawGUI(Shader* program) {
	pGUI->Draw(program);
}

void Player::CheckCollision() {

	Velocity += m_acceleration * Delta;
	m_acceleration = { 0, 0, 0 };

	CollisionTest();

	Position.x += Velocity.x * Delta;
	Position.y += Velocity.y * Delta;
	Position.z += Velocity.z * Delta;

	F3menuData.Position = Position;
}

void Player::PhysicUpdate() {
	if (!isFlying) {
		if (!isOnGround) {
			if(Velocity.y > -TERMINAL_VELOCITY) {
				m_acceleration.y -= GRAVITY;
			}
		}
	}

	// drag
	float drag = 0.95 * Delta; // this is temporary, until better implementation 
	if(isOnGround) drag *= 5;
	Velocity.x *= -drag + 1;
	Velocity.z *= -drag + 1;

	if(isFlying) {
		Velocity.y *= -drag + 1;
	}
}

void Player::KeyBoardUpdate() {
	float currentTime = glfwGetTime();
	Delta = currentTime - LastTime;
	LastTime = currentTime;
	
	FPSCounter++;


	if (currentTime - LastFPSTime >= 1.0) {
		F3menuData.FPS = FPSCounter;
		FPSCounter = 0;
		LastFPSTime += 1;
		
	}

	FOV = FOVSettings;

	// Events test
	if (Events::JustPressed(KM_KEY_ESCAPE)) {
		Window::SetWindowShouldClose(true);
	}
	if (Events::JustPressed(KM_KEY_TAB)) {
		Events::ToogleCursor();
	}

	if (Events::lockedCursor) {

		if (Events::JustClicked(KM_MOUSE_BUTTON_1)) {
			glm::vec3 end;
			glm::vec3 norm;
			glm::vec3 iend;
			world->RayCast(camera->GetPosition(), View, 20.f, end, norm, iend);
			if (world->GetBlock(iend.x, iend.y, iend.z)->GetID() != 0) {
				world->SetBlock_u(0, iend.x, iend.y, iend.z);
			}
		}

		if (Events::JustClicked(KM_MOUSE_BUTTON_2)) {
			glm::vec3 end;
			glm::vec3 norm;
			glm::vec3 iend;
			world->RayCast(camera->GetPosition(), View, 20.f, end, norm, iend);
			if (world->GetBlock(iend.x, iend.y, iend.z)->GetID() != 0) {
				world->SetBlock_u(F3menuData.ItemHandID, iend.x + norm.x, iend.y + norm.y, iend.z + norm.z);
			}
		}
		{
			float Speed = this->Speed;
			if(Events::Pressed(KM_KEY_LEFT_CONTROL)) {
				if(isOnGround) {
					Speed /= 2;
				}
				else if(isFlying){
					m_acceleration.y -= Speed;
				}
			}
			if(Events::Pressed(KM_KEY_LEFT_SHIFT)) {
				Speed *= 1.5;
				FOV = FOVSettings + 15;
			}
			if(isOnGround) Speed *= 4;
			if(Events::Pressed(KM_KEY_W)) {

				m_acceleration.x += cos(radians(yaw)) * Speed;
				m_acceleration.z += sin(radians(yaw)) * Speed;
			}

			if(Events::Pressed(KM_KEY_S)) {
				m_acceleration.x -= cos(radians(yaw)) * Speed;
				m_acceleration.z -= sin(radians(yaw)) * Speed;
			}

			if(Events::Pressed(KM_KEY_D)) {
				m_acceleration.x -= cos(radians(yaw - 90)) * Speed;
				m_acceleration.z -= sin(radians(yaw - 90)) * Speed;
			}

			if(Events::Pressed(KM_KEY_A)) {
				m_acceleration.x += cos(radians(yaw - 90)) * Speed;
				m_acceleration.z += sin(radians(yaw - 90)) * Speed;
			}

			if(Events::Pressed(KM_KEY_SPACE)) {
				if(isFlying) {
					m_acceleration.y += Speed;
				}
				else {
					if(isOnGround) {
						Velocity.y = JumpForce;
					}
				}
			}
		}
		if (Events::JustPressed(KM_KEY_V)) {
			isFlyOn = !isFlyOn;
		}
		if (Events::JustPressed(KM_KEY_F3)) {
			pGUI->ToggleF3menu();

		}
		MouseUpdate();
		ScrollUpdate();
	}
}

void Player::MouseUpdate() {
	yaw += Events::deltaX * 0.15;
	pitch += Events::deltaY * 0.15;
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	if (yaw > 360) {
		yaw = 0;
	}
	if (yaw < 0) {
		yaw = 360;
	}
	glm::vec3 view_;
	view_.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	view_.y = sin(glm::radians(pitch));
	view_.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	View = glm::normalize(view_);
}

Camera* Player::getCamera() {
	return camera;
}

Player::~Player() {
	delete camera;
}

void Player::CollisionTest() {
	float definition = 0.1;

	bool yNeg_Obstructed = false;
	bool yPos_Obstructed = false;
	for(float x = Position.x - Dimensions.x; x <= Position.x + Dimensions.x; x += definition) {
		for(float z = Position.z - Dimensions.z; z <= Position.z + Dimensions.z; z += definition) {
			if(world->GetObstruction(x, Position.y, z)) {
				yNeg_Obstructed = true;
			}
			if(world->GetObstruction(x, Position.y + Dimensions.y, z)) {
				yPos_Obstructed = true;
			}
		}
	}

	bool zNeg_Obstructed = false;
	bool zPos_Obstructed = false;
	for(float x = Position.x - Dimensions.x + definition * 2; x <= Position.x + Dimensions.x; x += definition) {
		for(float y = Position.y + definition*2; y <= Position.y + Dimensions.y; y += definition) {
			if(world->GetObstruction(x, y, Position.z - Dimensions.z)) {
				zNeg_Obstructed = true;
			}
			if(world->GetObstruction(x, y, Position.z + Dimensions.z)) {
					zPos_Obstructed = true;
			}
		}
	}

	bool xNeg_Obstructed = false;
	bool xPos_Obstructed = false;
	for(float z = Position.z - Dimensions.z + definition * 2; z <= Position.z + Dimensions.z; z += definition) {
		for(float y = Position.y + definition * 2; y <= Position.y + Dimensions.y; y += definition) {
			if(world->GetObstruction(Position.x - Dimensions.x, y, z)) {
				xNeg_Obstructed = true;
			}
			if(world->GetObstruction(Position.x + Dimensions.x, y, z)) {
				xPos_Obstructed = true;
			}
		}
	}

	if(yNeg_Obstructed) {
		isOnGround = true;
		if(Velocity.y < 0) {
			Velocity.y = 0;
		}
	}
	else {
		isOnGround = false;
	}

	if(Velocity.y < 0 && yNeg_Obstructed) {
		Velocity.y = 0;
	}
	else if(Velocity.y > 0 && yPos_Obstructed) {
		Velocity.y = 0;
	}

	if(Velocity.x < 0 && xNeg_Obstructed) {
		Velocity.x = 0;
	}
	else if(Velocity.x > 0 && xPos_Obstructed) {
		Velocity.x = 0;
	}

	if(Velocity.z < 0 && zNeg_Obstructed) {
		Velocity.z = 0;
	}
	else if(Velocity.z > 0 && zPos_Obstructed) {
		Velocity.z = 0;
	}
}

void Player::ScrollUpdate() {
	F3menuData.ItemHandID = Events::deltaScrollY;

	if (F3menuData.ItemHandID > MaxID * 8) {
		F3menuData.ItemHandID = 4;
		Events::deltaScrollY = 4;
	}

	if (F3menuData.ItemHandID > MaxID) {
		F3menuData.ItemHandID = 0;
		Events::deltaScrollY = 0;
	}

	
}

